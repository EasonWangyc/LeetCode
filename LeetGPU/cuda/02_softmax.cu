/*
Softmax —— LeetGPU Medium
https://leetgpu.com/challenges/softmax

对矩阵的每一行做 softmax：y[i][j] = exp(x[i][j] - max_i) / sum_j exp(x[i][j] - max_i)

思路：
1. 一个 block 处理一行，block 内所有线程协作完成两次归约（求 max、求和）
2. 先减 max 再 exp —— 否则 exp(大数) 会溢出成 inf，这是 softmax 唯一的坑
3. 归约用共享内存 + 折半：stride 从 BLOCK/2 递减，tid < stride 的线程累加另一半
4. 每次写共享内存后都要 __syncthreads()；归约结束后所有线程都读 s[0]，
   再次复用共享内存前必须再 __syncthreads() 一次（否则会覆盖别人还没读的值）

注意：attention 里 softmax 的输入叫"分数"，通常 cols 远小于 BLOCK，
所以 for (j = tid; j < cols; j += BLOCK) 这个写法在高维下同样正确。

编译运行：
  nvcc -arch=sm_89 -O2 -o /tmp/softmax 02_softmax.cu && /tmp/softmax
*/
#include <cstdio>
#include <cmath>
#include <cfloat>
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

// 折半归约求 block 内最大值；调用方在再次复用 s 之前需要自己 __syncthreads()
template <int BLOCK>
__device__ __forceinline__ float block_reduce_max(float val, float* s) {
    int tid = threadIdx.x;
    s[tid] = val;
    __syncthreads();
    for (int stride = BLOCK / 2; stride > 0; stride >>= 1) {
        if (tid < stride) s[tid] = fmaxf(s[tid], s[tid + stride]);
        __syncthreads();
    }
    return s[0];
}

template <int BLOCK>
__device__ __forceinline__ float block_reduce_sum(float val, float* s) {
    int tid = threadIdx.x;
    s[tid] = val;
    __syncthreads();
    for (int stride = BLOCK / 2; stride > 0; stride >>= 1) {
        if (tid < stride) s[tid] += s[tid + stride];
        __syncthreads();
    }
    return s[0];
}

template <int BLOCK>
__global__ void softmax_kernel(const float* x, float* y, int rows, int cols) {
    __shared__ float s[BLOCK];
    const int row = blockIdx.x;
    const int tid = threadIdx.x;
    const float* xr = x + static_cast<size_t>(row) * cols;
    float* yr = y + static_cast<size_t>(row) * cols;

    // 1. 该行最大值
    float local_max = -FLT_MAX;
    for (int j = tid; j < cols; j += BLOCK) local_max = fmaxf(local_max, xr[j]);
    float m = block_reduce_max<BLOCK>(local_max, s);
    __syncthreads();  // 复用 s 前必须同步

    // 2. exp(x - max) 并顺便求分母
    float local_sum = 0.0f;
    for (int j = tid; j < cols; j += BLOCK) {
        float e = expf(xr[j] - m);
        yr[j] = e;
        local_sum += e;
    }
    float sum = block_reduce_sum<BLOCK>(local_sum, s);
    __syncthreads();

    // 3. 归一化
    float inv = 1.0f / sum;
    for (int j = tid; j < cols; j += BLOCK) yr[j] *= inv;
}

static void softmax_cpu(const float* x, float* y, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        const float* xr = x + static_cast<size_t>(r) * cols;
        float* yr = y + static_cast<size_t>(r) * cols;
        float m = xr[0];
        for (int j = 1; j < cols; ++j) m = fmaxf(m, xr[j]);
        float sum = 0.0f;
        for (int j = 0; j < cols; ++j) {
            yr[j] = expf(xr[j] - m);
            sum += yr[j];
        }
        for (int j = 0; j < cols; ++j) yr[j] /= sum;
    }
}

int main() {
    const int rows = 64;
    const int cols = 100;  // 故意大于 block 内实际参与计算的范围，验证 += BLOCK 的循环写法
    const size_t n = static_cast<size_t>(rows) * cols;
    const size_t bytes = n * sizeof(float);

    float* h_x = new float[n];
    float* h_y = new float[n];
    float* h_ref = new float[n];
    // 用较大的值（含负数）当输入，专门制造 exp 溢出，检验 max 减得对不对
    for (size_t i = 0; i < n; ++i) {
        h_x[i] = (static_cast<float>(i % 37) - 18.0f) * 20.0f;
    }
    softmax_cpu(h_x, h_ref, rows, cols);

    float *d_x, *d_y;
    CUDA_CHECK(cudaMalloc(&d_x, bytes));
    CUDA_CHECK(cudaMalloc(&d_y, bytes));
    CUDA_CHECK(cudaMemcpy(d_x, h_x, bytes, cudaMemcpyHostToDevice));

    constexpr int BLOCK = 128;
    softmax_kernel<BLOCK><<<rows, BLOCK>>>(d_x, d_y, rows, cols);
    CUDA_CHECK(cudaDeviceSynchronize());
    CUDA_CHECK(cudaMemcpy(h_y, d_y, bytes, cudaMemcpyDeviceToHost));

    float max_err = 0.0f;
    for (size_t i = 0; i < n; ++i) max_err = fmaxf(max_err, fabsf(h_y[i] - h_ref[i]));
    // 每行概率和应当为 1
    float worst_row_sum = 0.0f;
    for (int r = 0; r < rows; ++r) {
        float s = 0.0f;
        for (int j = 0; j < cols; ++j) s += h_y[static_cast<size_t>(r) * cols + j];
        worst_row_sum = fmaxf(worst_row_sum, fabsf(s - 1.0f));
    }
    printf("max_abs_err      = %.3e\n", max_err);
    printf("max |rowsum - 1| = %.3e\n", worst_row_sum);
    printf("-> %s\n", (max_err < 1e-5f && worst_row_sum < 1e-5f) ? "PASS" : "FAIL");

    cudaFree(d_x); cudaFree(d_y);
    delete[] h_x; delete[] h_y; delete[] h_ref;
    return (max_err < 1e-5f && worst_row_sum < 1e-5f) ? 0 : 1;
}
