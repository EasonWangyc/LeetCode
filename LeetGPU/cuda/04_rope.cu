/*
RoPE (Rotary Position Embedding) —— LLM 组件（LeetGPU 暂无此题）

把位置信息以「旋转」的方式注入 q/k：对向量的每一对相邻分量 (x_{2i}, x_{2i+1})，
按位置 pos 旋转角度 θ_i = pos * base^(-2i/d)：

  y_{2i}   = x_{2i}   * cos θ_i - x_{2i+1} * sin θ_i
  y_{2i+1} = x_{2i}   * sin θ_i + x_{2i+1} * cos θ_i

为什么这么设计（面试常问）：
1. 旋转是正交变换，所以不改变向量长度 —— 不会破坏 q·k 的尺度
2. 关键性质：<RoPE(q, m), RoPE(k, n)> 只依赖 m - n，与绝对位置无关。
   因为两个旋转的夹角只由 (m-n) 决定。这让模型天然获得相对位置感，
   且可以外推到训练时没见过的长度（配合 NTK / YaRN 之类的频率缩放）
3. 作用在 q、k 上，不作用在 v 上 —— v 只是被加权求和，不需要位置信息

实现细节：
- 上面是「交错对」(interleaved) 写法；HuggingFace 用的是「前后半」(rotate_half)：
  把向量劈成 [x[:d/2], x[d/2:]] 再旋转。两者只差一个固定的置换，数学等价
- 工程实现会预计算一张 [max_seq_len, d/2] 的 cos/sin 表，kernel 里直接查表，
  避免每个元素都算一次 powf/cosf/sinf（下面的 kernel 为了自包含是现算的）

编译运行：
  nvcc -arch=sm_89 -O2 -o /tmp/rope 04_rope.cu && /tmp/rope
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

__global__ void rope_kernel(const float* x, const float* pos, float* y,
                            int rows, int d, float base) {
    const int row = blockIdx.x;
    const int tid = threadIdx.x;
    const float* xr = x + static_cast<size_t>(row) * d;
    float* yr = y + static_cast<size_t>(row) * d;
    const float p = pos[row];
    const int half = d / 2;

    for (int i = tid; i < half; i += blockDim.x) {
        // θ_i = pos * base^(-2i/d)
        float theta = p * powf(base, -2.0f * static_cast<float>(i) / static_cast<float>(d));
        float c = cosf(theta);
        float s = sinf(theta);
        float x0 = xr[2 * i];
        float x1 = xr[2 * i + 1];
        yr[2 * i]     = x0 * c - x1 * s;
        yr[2 * i + 1] = x0 * s + x1 * c;
    }
}

static void rope_cpu(const float* x, const float* pos, float* y,
                     int rows, int d, float base) {
    for (int r = 0; r < rows; ++r) {
        const float* xr = x + static_cast<size_t>(r) * d;
        float* yr = y + static_cast<size_t>(r) * d;
        for (int i = 0; i < d / 2; ++i) {
            float theta = pos[r] * powf(base, -2.0f * static_cast<float>(i) / static_cast<float>(d));
            float c = cosf(theta), s = sinf(theta);
            float x0 = xr[2 * i], x1 = xr[2 * i + 1];
            yr[2 * i]     = x0 * c - x1 * s;
            yr[2 * i + 1] = x0 * s + x1 * c;
        }
    }
}

static float dot(const float* a, const float* b, int n) {
    float acc = 0.0f;
    for (int i = 0; i < n; ++i) acc += a[i] * b[i];
    return acc;
}

int main() {
    const int rows = 8;   // 位置 0..7
    const int d = 16;
    const float base = 10000.0f;
    const size_t n = static_cast<size_t>(rows) * d;
    const size_t bytes = n * sizeof(float);

    float* h_x = new float[n];
    float* h_pos = new float[rows];
    float* h_y = new float[n];
    float* h_ref = new float[n];
    // 每行用同一个向量，这样 <y_i, y_j> 应当只依赖 i-j，可以直接检验相对位置性质
    for (int r = 0; r < rows; ++r) {
        h_pos[r] = static_cast<float>(r);
        for (int j = 0; j < d; ++j) {
            h_x[static_cast<size_t>(r) * d + j] = sinf(0.7f * static_cast<float>(r) + static_cast<float>(j)) + 0.5f;
        }
    }
    // 让每一行内容相同：复制第 0 行
    for (int r = 1; r < rows; ++r) {
        for (int j = 0; j < d; ++j) {
            h_x[static_cast<size_t>(r) * d + j] = h_x[j];
        }
    }
    rope_cpu(h_x, h_pos, h_ref, rows, d, base);

    float *d_x, *d_pos, *d_y;
    CUDA_CHECK(cudaMalloc(&d_x, bytes));
    CUDA_CHECK(cudaMalloc(&d_pos, rows * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_y, bytes));
    CUDA_CHECK(cudaMemcpy(d_x, h_x, bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_pos, h_pos, rows * sizeof(float), cudaMemcpyHostToDevice));

    rope_kernel<<<rows, 64>>>(d_x, d_pos, d_y, rows, d, base);
    CUDA_CHECK(cudaDeviceSynchronize());
    CUDA_CHECK(cudaMemcpy(h_y, d_y, bytes, cudaMemcpyDeviceToHost));

    // 检查 1：与 CPU 参考一致
    float max_err = 0.0f;
    for (size_t i = 0; i < n; ++i) max_err = fmaxf(max_err, fabsf(h_y[i] - h_ref[i]));

    // 检查 2：旋转不改变长度
    float worst_norm = 0.0f;
    for (int r = 0; r < rows; ++r) {
        const float* xr = h_x + static_cast<size_t>(r) * d;
        const float* yr = h_y + static_cast<size_t>(r) * d;
        float nx = 0.0f, ny = 0.0f;
        for (int j = 0; j < d; ++j) { nx += xr[j] * xr[j]; ny += yr[j] * yr[j]; }
        worst_norm = fmaxf(worst_norm, fabsf(sqrtf(nx) - sqrtf(ny)));
    }

    // 检查 3：相对位置性质 —— <y_i, y_j> 只依赖 (i - j)
    // 输入每行相同，所以同一「间隔」的所有点积都应当相等
    float worst_rel = 0.0f;
    for (int diff = 1; diff < rows / 2; ++diff) {
        float first = dot(h_y + 0 * d, h_y + diff * d, d);
        for (int i = 1; i + diff < rows; ++i) {
            float cur = dot(h_y + static_cast<size_t>(i) * d,
                            h_y + static_cast<size_t>(i + diff) * d, d);
            worst_rel = fmaxf(worst_rel, fabsf(cur - first));
        }
    }

    printf("max_abs_err              = %.3e\n", max_err);
    printf("max |‖y‖ - ‖x‖|          = %.3e\n", worst_norm);
    printf("max <y_i,y_j> 同间隔偏差  = %.3e\n", worst_rel);
    int ok = (max_err < 1e-5f && worst_norm < 1e-5f && worst_rel < 1e-5f);
    printf("-> %s\n", ok ? "PASS" : "FAIL");

    cudaFree(d_x); cudaFree(d_pos); cudaFree(d_y);
    delete[] h_x; delete[] h_pos; delete[] h_y; delete[] h_ref;
    return ok ? 0 : 1;
}
