/*
Layer Normalization —— LLM 基础组件（LeetGPU 暂无此题）

对最后一维做归一化，再仿射变换：
  y = (x - mean) / sqrt(var + eps) * gamma + beta
  其中 mean、var 都是沿最后一维（特征维）统计的，与 batch、seq 无关

和 BatchNorm 的区别：LayerNorm 每个样本自己算统计量，不跨 batch，
所以推理和训练行为一致，seq_len 变化也不受影响 —— 这是 Transformer 用它的原因。

思路：
1. 一个 block 处理一行，两次 block 归约：先求 mean，再求方差
2. 两趟扫描而不是 E[x²]-E[x]² 一趟出结果：后者在数值上会灾难性抵消
   （x 的均值很大、方差很小时，两个大数相减把有效位吃光）
3. rsqrtf 算 1/sqrt，比 1.0f/sqrtf 快且精度够

编译运行：
  nvcc -arch=sm_89 -O2 -o /tmp/layernorm 03_layer-norm.cu && /tmp/layernorm
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
__global__ void layer_norm_kernel(const float* x, const float* gamma, const float* beta,
                                  float* y, int rows, int cols, float eps) {
    __shared__ float s[BLOCK];
    const int row = blockIdx.x;
    const int tid = threadIdx.x;
    const float* xr = x + static_cast<size_t>(row) * cols;
    float* yr = y + static_cast<size_t>(row) * cols;

    // 1. mean
    float local_sum = 0.0f;
    for (int j = tid; j < cols; j += BLOCK) local_sum += xr[j];
    float mean = block_reduce_sum<BLOCK>(local_sum, s) / cols;
    __syncthreads();

    // 2. variance（第二趟：对 (x - mean)^2 再归约一次）
    float local_var = 0.0f;
    for (int j = tid; j < cols; j += BLOCK) {
        float d = xr[j] - mean;
        local_var += d * d;
    }
    float var = block_reduce_sum<BLOCK>(local_var, s) / cols;
    __syncthreads();

    // 3. 归一化 + 仿射
    float inv_std = rsqrtf(var + eps);
    for (int j = tid; j < cols; j += BLOCK) {
        yr[j] = (xr[j] - mean) * inv_std * gamma[j] + beta[j];
    }
}

static void layer_norm_cpu(const float* x, const float* gamma, const float* beta,
                           float* y, int rows, int cols, float eps) {
    for (int r = 0; r < rows; ++r) {
        const float* xr = x + static_cast<size_t>(r) * cols;
        float* yr = y + static_cast<size_t>(r) * cols;
        float mean = 0.0f;
        for (int j = 0; j < cols; ++j) mean += xr[j];
        mean /= cols;
        float var = 0.0f;
        for (int j = 0; j < cols; ++j) {
            float d = xr[j] - mean;
            var += d * d;
        }
        var /= cols;
        float inv_std = 1.0f / sqrtf(var + eps);
        for (int j = 0; j < cols; ++j) {
            yr[j] = (xr[j] - mean) * inv_std * gamma[j] + beta[j];
        }
    }
}

int main() {
    const int rows = 32;
    const int cols = 512;
    const size_t n = static_cast<size_t>(rows) * cols;
    const size_t bytes = n * sizeof(float);
    const float eps = 1e-5f;

    float* h_x = new float[n];
    float* h_g = new float[cols];
    float* h_b = new float[cols];
    float* h_y = new float[n];
    float* h_ref = new float[n];

    // 均值远离 0（128 附近），此时 E[x²]-E[x]² 的一趟法会严重损失精度；
    // 取值都是整数，float32 可精确表示，所以 CPU 与 GPU 只应差在归约顺序上
    for (int r = 0; r < rows; ++r) {
        for (int j = 0; j < cols; ++j) {
            h_x[static_cast<size_t>(r) * cols + j] =
                128.0f + static_cast<float>((r * 7 + j) % 23) - 11.0f;
        }
    }
    for (int j = 0; j < cols; ++j) {
        h_g[j] = 1.0f + 0.1f * static_cast<float>(j % 5);
        h_b[j] = 0.5f * static_cast<float>(j % 3);
    }
    layer_norm_cpu(h_x, h_g, h_b, h_ref, rows, cols, eps);

    float *d_x, *d_g, *d_b, *d_y;
    CUDA_CHECK(cudaMalloc(&d_x, bytes));
    CUDA_CHECK(cudaMalloc(&d_g, cols * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_b, cols * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_y, bytes));
    CUDA_CHECK(cudaMemcpy(d_x, h_x, bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_g, h_g, cols * sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_b, h_b, cols * sizeof(float), cudaMemcpyHostToDevice));

    constexpr int BLOCK = 256;
    layer_norm_kernel<BLOCK><<<rows, BLOCK>>>(d_x, d_g, d_b, d_y, rows, cols, eps);
    CUDA_CHECK(cudaDeviceSynchronize());
    CUDA_CHECK(cudaMemcpy(h_y, d_y, bytes, cudaMemcpyDeviceToHost));

    float max_err = 0.0f;
    for (size_t i = 0; i < n; ++i) max_err = fmaxf(max_err, fabsf(h_y[i] - h_ref[i]));

    // 附带检查：gamma=1, beta=0 时，每行输出应当均值 0、方差 1
    float worst_mean = 0.0f, worst_var = 0.0f;
    for (int r = 0; r < rows; ++r) {
        const float* yr = h_y + static_cast<size_t>(r) * cols;
        // 反仿射回去：(y - beta) / gamma
        float mean = 0.0f;
        for (int j = 0; j < cols; ++j) mean += (yr[j] - h_b[j]) / h_g[j];
        mean /= cols;
        float var = 0.0f;
        for (int j = 0; j < cols; ++j) {
            float v = (yr[j] - h_b[j]) / h_g[j] - mean;
            var += v * v;
        }
        var /= cols;
        worst_mean = fmaxf(worst_mean, fabsf(mean));
        worst_var = fmaxf(worst_var, fabsf(var - 1.0f));
    }
    printf("max_abs_err        = %.3e\n", max_err);
    printf("max |mean|         = %.3e\n", worst_mean);
    printf("max |var - 1|      = %.3e\n", worst_var);
    printf("-> %s\n", (max_err < 1e-4f && worst_mean < 1e-4f && worst_var < 1e-3f) ? "PASS" : "FAIL");

    cudaFree(d_x); cudaFree(d_g); cudaFree(d_b); cudaFree(d_y);
    delete[] h_x; delete[] h_g; delete[] h_b; delete[] h_y; delete[] h_ref;
    return (max_err < 1e-4f && worst_mean < 1e-4f && worst_var < 1e-3f) ? 0 : 1;
}
