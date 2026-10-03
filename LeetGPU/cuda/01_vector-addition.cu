/*
Vector Addition —— LeetGPU Easy
https://leetgpu.com/challenges/vector-addition

给定等长向量 a、b，计算 c = a + b（逐元素）。

思路：
1. 一个线程负责一个元素，全局线程号 i = blockIdx.x * blockDim.x + threadIdx.x
2. 网格大小 = ceil(n / blockSize)，所以线程总数可能超过 n，必须判越界
3. 这是 CUDA 的 "hello world"，但三个必备要素一个不少：
   cudaMalloc / cudaMemcpy / kernel<<<grid, block>>> / cudaDeviceSynchronize

编译运行：
  nvcc -arch=sm_89 -O2 -o /tmp/vadd 01_vector-addition.cu && /tmp/vadd
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

__global__ void vector_add_kernel(const float* a, const float* b, float* c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}

// CPU 参考实现，用来对拍
static void vector_add_cpu(const float* a, const float* b, float* c, int n) {
    for (int i = 0; i < n; ++i) c[i] = a[i] + b[i];
}

static int check(const float* got, const float* want, int n) {
    float max_err = 0.0f;
    for (int i = 0; i < n; ++i) {
        max_err = fmaxf(max_err, fabsf(got[i] - want[i]));
    }
    printf("max_abs_err = %.3e  ->  %s\n", max_err, max_err < 1e-5f ? "PASS" : "FAIL");
    return max_err < 1e-5f;
}

int main() {
    // 故意取一个不是 blockSize 整数倍的长度，验证越界判断
    const int n = 1000;
    const size_t bytes = n * sizeof(float);

    float* h_a = new float[n];
    float* h_b = new float[n];
    float* h_c = new float[n];
    float* h_ref = new float[n];
    for (int i = 0; i < n; ++i) {
        h_a[i] = static_cast<float>(i);
        h_b[i] = static_cast<float>(2 * i);
    }
    vector_add_cpu(h_a, h_b, h_ref, n);

    float *d_a, *d_b, *d_c;
    CUDA_CHECK(cudaMalloc(&d_a, bytes));
    CUDA_CHECK(cudaMalloc(&d_b, bytes));
    CUDA_CHECK(cudaMalloc(&d_c, bytes));
    CUDA_CHECK(cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice));

    const int block_size = 256;
    const int grid_size = (n + block_size - 1) / block_size;
    vector_add_kernel<<<grid_size, block_size>>>(d_a, d_b, d_c, n);
    CUDA_CHECK(cudaDeviceSynchronize());

    CUDA_CHECK(cudaMemcpy(h_c, d_c, bytes, cudaMemcpyDeviceToHost));
    int ok = check(h_c, h_ref, n);

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    delete[] h_a; delete[] h_b; delete[] h_c; delete[] h_ref;
    return ok ? 0 : 1;
}
