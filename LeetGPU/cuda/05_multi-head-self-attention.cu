/*
Multi-Head Self-Attention —— LeetGPU Hard
https://leetgpu.com/challenges/multi-head-self-attention

Attention(Q,K,V) = softmax(QKᵀ / √d_head + mask) V
多头就是把 d_model 切成 H 份，每份独立做一次 attention，最后拼回来再投影。

本文件把整个前向拆成三个 kernel，和真实实现的结构一致：
  1. matmul_kernel     —— X 分别乘 Wq / Wk / Wv 得到 Q、K、V
  2. attention_kernel  —— 每个 block 负责一个 (batch, head, query) 输出行
  3. matmul_kernel     —— 拼好的多头输出乘 Wo

思路要点：
1. 缩放因子 1/√d_head 不能省：d_head 越大 q·k 的点积方差越大，
   不缩放会把 softmax 推到饱和区，梯度几乎为 0
2. causal mask：第 i 个 query 只能看 j <= i 的 key，其余位置置 -inf
   置 -inf 而不是 0，是因为 exp(-inf) = 0，softmax 后权重自然为 0；
   置 0 会让它们参与竞争
3. head 的切分：Q[b][i][h*hd + d]，即把 d_model 均分后连续存放
   （HuggingFace 用 [h][d] 的转置布局，只是索引写法不同）
4. 这里一个 block 只算一行，是为了好读；真实实现会把多个 query 合到一个 block，
   并把 scores 留在寄存器/共享内存里避免反复读显存 —— 这是 flash attention 的起点

编译运行：
  nvcc -arch=sm_89 -O2 -o /tmp/mha 05_multi-head-self-attention.cu && /tmp/mha
*/
#include <cstdio>
#include <cmath>
#include <cuda_runtime.h>

#define CUDA_CHECK(call)                                                     \
    do {                                                                     \
        cudaError_t err = (call);                                            \
        if (err != cudaSuccess) {                                            \
            printf("CUDA error %s:%d: %s\n", __FILE__, __LINE__,             \
                   cudaGetErrorString(err));                                 \
            return 1;                                                        \
        }                                                                    \
    } while (0)

#define MAX_S 128

// ---------------------------------------------------------------- kernel 1
// C[M,N] = A[M,K] @ B[K,N]，一行一线程的朴素版
__global__ void matmul_kernel(const float* A, const float* B, float* C,
                              int M, int K, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < M && col < N) {
        float acc = 0.0f;
        for (int k = 0; k < K; ++k) acc += A[row * K + k] * B[k * N + col];
        C[row * N + col] = acc;
    }
}

// ---------------------------------------------------------------- kernel 2
// 一个 block = 一个 (b, h, i)，算第 i 个 query 在 head h 上的输出向量
__global__ void attention_kernel(const float* Q, const float* K, const float* V,
                                 float* O, int B, int S, int H, int hd,
                                 float scale) {
    __shared__ float prob[MAX_S];
    const int i = blockIdx.x % S;
    const int h = (blockIdx.x / S) % H;
    const int b = blockIdx.x / (S * H);
    const int tid = threadIdx.x;
    const int D = H * hd;
    const float* q = Q + (static_cast<size_t>(b) * S + i) * D + h * hd;

    // 1. 分数 scores[j] = q·k_j * scale，causal 之外置 -inf
    float sc = -INFINITY;
    if (tid < S && tid <= i) {
        const float* k = K + (static_cast<size_t>(b) * S + tid) * D + h * hd;
        float acc = 0.0f;
        for (int d = 0; d < hd; ++d) acc += q[d] * k[d];
        sc = acc * scale;
    }

    // 2. warp 内归约求 max（blockDim = 32，正好一个 warp）
    float m = sc;
    for (int off = 16; off > 0; off >>= 1)
        m = fmaxf(m, __shfl_xor_sync(0xffffffffu, m, off));

    // 3. exp 并求分母；被 mask 的位置 exp(-inf) = 0，自然不参与
    float e = expf(sc - m);
    float sum = e;
    for (int off = 16; off > 0; off >>= 1)
        sum += __shfl_xor_sync(0xffffffffu, sum, off);

    if (tid < S) prob[tid] = e / sum;
    __syncthreads();  // prob 要被所有线程读，写完之后必须同步

    // 4. 加权求和：out[d] = Σ_{j<=i} prob[j] * v_j[d]
    for (int d = tid; d < hd; d += blockDim.x) {
        float acc = 0.0f;
        for (int j = 0; j <= i; ++j) {
            const float* v = V + (static_cast<size_t>(b) * S + j) * D + h * hd;
            acc += prob[j] * v[d];
        }
        O[(static_cast<size_t>(b) * S + i) * D + h * hd + d] = acc;
    }
}

// ------------------------------------------------------------- CPU 参考实现
static void matmul_cpu(const float* A, const float* B, float* C, int M, int K, int N) {
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            float acc = 0.0f;
            for (int k = 0; k < K; ++k) acc += A[i * K + k] * B[k * N + j];
            C[i * N + j] = acc;
        }
}

static void attention_cpu(const float* Q, const float* K, const float* V, float* O,
                          int B, int S, int H, int hd, float scale) {
    const int D = H * hd;
    for (int b = 0; b < B; ++b)
        for (int h = 0; h < H; ++h)
            for (int i = 0; i < S; ++i) {
                const float* q = Q + (static_cast<size_t>(b) * S + i) * D + h * hd;
                float scores[MAX_S];
                float m = -INFINITY;
                for (int j = 0; j < S; ++j) {
                    if (j > i) { scores[j] = -INFINITY; continue; }
                    const float* k = K + (static_cast<size_t>(b) * S + j) * D + h * hd;
                    float acc = 0.0f;
                    for (int d = 0; d < hd; ++d) acc += q[d] * k[d];
                    scores[j] = acc * scale;
                    m = fmaxf(m, scores[j]);
                }
                float sum = 0.0f;
                for (int j = 0; j <= i; ++j) { scores[j] = expf(scores[j] - m); sum += scores[j]; }
                for (int d = 0; d < hd; ++d) {
                    float acc = 0.0f;
                    for (int j = 0; j <= i; ++j) {
                        const float* v = V + (static_cast<size_t>(b) * S + j) * D + h * hd;
                        acc += scores[j] / sum * v[d];
                    }
                    O[(static_cast<size_t>(b) * S + i) * D + h * hd + d] = acc;
                }
            }
}

// --------------------------------------------------------------- 测试脚手架
struct Dims { int B, S, D, H, hd; };

// 跑完整前向：Y = MHA(X)
static void forward_gpu(const Dims& dm, const float* d_X, const float* d_Wq,
                        const float* d_Wk, const float* d_Wv, const float* d_Wo,
                        float* d_Q, float* d_K, float* d_V, float* d_O, float* d_Y) {
    const int M = dm.B * dm.S;
    dim3 block(16, 16);
    dim3 grid((dm.D + 15) / 16, (M + 15) / 16);
    const float scale = 1.0f / sqrtf(static_cast<float>(dm.hd));

    matmul_kernel<<<grid, block>>>(d_X, d_Wq, d_Q, M, dm.D, dm.D);
    matmul_kernel<<<grid, block>>>(d_X, d_Wk, d_K, M, dm.D, dm.D);
    matmul_kernel<<<grid, block>>>(d_X, d_Wv, d_V, M, dm.D, dm.D);
    attention_kernel<<<dm.B * dm.H * dm.S, 32>>>(d_Q, d_K, d_V, d_O,
                                                 dm.B, dm.S, dm.H, dm.hd, scale);
    matmul_kernel<<<grid, block>>>(d_O, d_Wo, d_Y, M, dm.D, dm.D);
}

static void forward_cpu(const Dims& dm, const float* X, const float* Wq,
                        const float* Wk, const float* Wv, const float* Wo,
                        float* Q, float* K, float* V, float* O, float* Y) {
    const int M = dm.B * dm.S;
    const float scale = 1.0f / sqrtf(static_cast<float>(dm.hd));
    matmul_cpu(X, Wq, Q, M, dm.D, dm.D);
    matmul_cpu(X, Wk, K, M, dm.D, dm.D);
    matmul_cpu(X, Wv, V, M, dm.D, dm.D);
    attention_cpu(Q, K, V, O, dm.B, dm.S, dm.H, dm.hd, scale);
    matmul_cpu(O, Wo, Y, M, dm.D, dm.D);
}

int main() {
    const Dims dm{2, 4, 8, 2, 4};  // B, S, D, H, head_dim —— d_model = D = H * hd
    const int M = dm.B * dm.S;
    const size_t xbytes = static_cast<size_t>(M) * dm.D * sizeof(float);
    const size_t wbytes = static_cast<size_t>(dm.D) * dm.D * sizeof(float);

    float* h_X = new float[M * dm.D];
    float* h_Wq = new float[dm.D * dm.D];
    float* h_Wk = new float[dm.D * dm.D];
    float* h_Wv = new float[dm.D * dm.D];
    float* h_Wo = new float[dm.D * dm.D];
    float* h_Y = new float[M * dm.D];
    float* h_ref = new float[M * dm.D];
    float* h_Q = new float[M * dm.D];
    float* h_K = new float[M * dm.D];
    float* h_V = new float[M * dm.D];
    float* h_O = new float[M * dm.D];
    float* tmp = new float[M * dm.D];

    for (int i = 0; i < M * dm.D; ++i) h_X[i] = 0.5f * sinf(0.9f * static_cast<float>(i)) + 0.1f * static_cast<float>(i % 5);
    for (int i = 0; i < dm.D * dm.D; ++i) {
        h_Wq[i] = 0.1f * static_cast<float>((i % 7) - 3);
        h_Wk[i] = 0.1f * static_cast<float>((i % 5) - 2);
        h_Wv[i] = 0.1f * static_cast<float>((i % 9) - 4);
        h_Wo[i] = 0.1f * static_cast<float>((i % 11) - 5);
    }
    forward_cpu(dm, h_X, h_Wq, h_Wk, h_Wv, h_Wo, h_Q, h_K, h_V, h_O, h_ref);

    float *d_X, *d_Wq, *d_Wk, *d_Wv, *d_Wo, *d_Q, *d_K, *d_V, *d_O, *d_Y;
    CUDA_CHECK(cudaMalloc(&d_X, xbytes));
    CUDA_CHECK(cudaMalloc(&d_Wq, wbytes));
    CUDA_CHECK(cudaMalloc(&d_Wk, wbytes));
    CUDA_CHECK(cudaMalloc(&d_Wv, wbytes));
    CUDA_CHECK(cudaMalloc(&d_Wo, wbytes));
    CUDA_CHECK(cudaMalloc(&d_Q, xbytes));
    CUDA_CHECK(cudaMalloc(&d_K, xbytes));
    CUDA_CHECK(cudaMalloc(&d_V, xbytes));
    CUDA_CHECK(cudaMalloc(&d_O, xbytes));
    CUDA_CHECK(cudaMalloc(&d_Y, xbytes));
    CUDA_CHECK(cudaMemcpy(d_X, h_X, xbytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_Wq, h_Wq, wbytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_Wk, h_Wk, wbytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_Wv, h_Wv, wbytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_Wo, h_Wo, wbytes, cudaMemcpyHostToDevice));

    forward_gpu(dm, d_X, d_Wq, d_Wk, d_Wv, d_Wo, d_Q, d_K, d_V, d_O, d_Y);
    CUDA_CHECK(cudaDeviceSynchronize());
    CUDA_CHECK(cudaMemcpy(h_Y, d_Y, xbytes, cudaMemcpyDeviceToHost));

    // 检查 1：与 CPU 参考一致
    float max_err = 0.0f;
    for (int i = 0; i < M * dm.D; ++i) max_err = fmaxf(max_err, fabsf(h_Y[i] - h_ref[i]));

    // 检查 2：因果性 —— 只改最后一个 token 的输入，前面 token 的输出必须一动不动
    const int last = M - 1;  // 最后一个 (b, i) 行
    for (int d = 0; d < dm.D; ++d) h_X[last * dm.D + d] += 10.0f;
    CUDA_CHECK(cudaMemcpy(d_X, h_X, xbytes, cudaMemcpyHostToDevice));
    forward_gpu(dm, d_X, d_Wq, d_Wk, d_Wv, d_Wo, d_Q, d_K, d_V, d_O, d_Y);
    CUDA_CHECK(cudaDeviceSynchronize());
    float* h_Y2 = new float[M * dm.D];
    CUDA_CHECK(cudaMemcpy(h_Y2, d_Y, xbytes, cudaMemcpyDeviceToHost));

    float causal_leak = 0.0f;   // 前面几行被影响的最大幅度，应当为 0
    float last_moved = 0.0f;    // 最后一行应当明显变化，否则说明改动没生效
    for (int b = 0; b < dm.B; ++b) {
        for (int i = 0; i < dm.S - 1; ++i) {
            int row = b * dm.S + i;
            for (int d = 0; d < dm.D; ++d)
                causal_leak = fmaxf(causal_leak, fabsf(h_Y2[row * dm.D + d] - h_Y[row * dm.D + d]));
        }
        int row = b * dm.S + (dm.S - 1);
        for (int d = 0; d < dm.D; ++d)
            last_moved = fmaxf(last_moved, fabsf(h_Y2[row * dm.D + d] - h_Y[row * dm.D + d]));
    }

    printf("max_abs_err vs CPU ref    = %.3e\n", max_err);
    printf("causal leak (应为 0)      = %.3e\n", causal_leak);
    printf("last token 变化量 (应 > 0) = %.3e\n", last_moved);
    int ok = (max_err < 1e-5f && causal_leak == 0.0f && last_moved > 1e-3f);
    printf("-> %s\n", ok ? "PASS" : "FAIL");

    cudaFree(d_X); cudaFree(d_Wq); cudaFree(d_Wk); cudaFree(d_Wv); cudaFree(d_Wo);
    cudaFree(d_Q); cudaFree(d_K); cudaFree(d_V); cudaFree(d_O); cudaFree(d_Y);
    delete[] h_X; delete[] h_Wq; delete[] h_Wk; delete[] h_Wv; delete[] h_Wo;
    delete[] h_Y; delete[] h_Y2; delete[] h_ref;
    delete[] h_Q; delete[] h_K; delete[] h_V; delete[] h_O; delete[] tmp;
    return ok ? 0 : 1;
}
