<div align="center">

# ⚡ LeetGPU

**CUDA 手写算子 · NumPy 参考实现 · 对齐 [LeetGPU](https://leetgpu.com/challenges) 题单**

<sub>跟着 LeetGPU 刷 kernel，顺带把 LLM 的组件一个个手写一遍。</sub>

</div>

---

## 📁 目录结构

```text
LeetGPU/
├── cuda/                          # CUDA kernel，每个 .cu 自带 CPU 参考实现 + 自测 main()
│   ├── 01_vector-addition.cu
│   ├── 02_softmax.cu
│   ├── 03_layer-norm.cu
│   ├── 04_rope.cu
│   └── 05_multi-head-self-attention.cu
└── numpy/                         # NumPy 参考实现，用来对拍 / 面试白板
    ├── attention.py
    └── rope.py
```

文件名 = `编号_平台题目 slug`：编号保持排序和刷题顺序，slug 直接对上 [LeetGPU 官网](https://leetgpu.com/challenges) 的题目地址。后两个（LayerNorm、RoPE）平台上没有对应题，属于 LLM 组件补充。

---

## ⚙️ 编译运行

每个 `.cu` 都是**自包含**的：内含 CPU 参考实现，跑完会打印误差并给出 `PASS / FAIL`，退出码可直接用于脚本。

```bash
cd LeetGPU/cuda

# 按本机 GPU 架构编译（RTX 4060 是 sm_89）；不确定就用 -arch=native
nvcc -arch=sm_89 -O2 -o /tmp/k 02_softmax.cu && /tmp/k

# 一次跑全部
for f in *.cu; do
  nvcc -arch=sm_89 -O2 -o "/tmp/${f%.cu}" "$f" && "/tmp/${f%.cu}"
done
```

NumPy 部分需要 `numpy`：

```bash
cd LeetGPU/numpy
python3 attention.py
python3 rope.py
```

---

## 🧩 CUDA 算子

| 文件 | 内容 | LeetGPU | 核心考点 |
|:---|:---|:---|:---|
| `01_vector-addition.cu` | 向量加法 | Easy · vector-addition | 线程索引、`ceil(n/block)` 后的越界判断、`CUDA_CHECK` 宏 |
| `02_softmax.cu` | 行 softmax | Medium · softmax | **先减 max 再 exp**（否则溢出）、共享内存折半归约、归约后复用共享内存前要 `__syncthreads()` |
| `03_layer-norm.cu` | LayerNorm | — | 两次归约（mean → var）、为什么不用 `E[x²]-E[x]²`、`rsqrtf` |
| `04_rope.cu` | 旋转位置编码 | — | 旋转角度构造、正交性、**相对位置性质**的数值验证 |
| `05_multi-head-self-attention.cu` | 多头自注意力 | Hard · multi-head-self-attention | 三 kernel 拆分（投影/注意力/输出投影）、warp shuffle 归约、causal mask 置 `-inf` |

每个文件顶部注释里有完整的思路说明和面试要点，下面只列最容易被追问的：

**softmax 为什么要减 max？**
`exp(1000)` 直接溢出成 `inf`，`inf/inf = nan`。减去每行最大值后最大指数是 `exp(0)=1`，数学上等价、数值上安全。

**LayerNorm 为什么用两趟而不是 `E[x²]-E[x]²`？**
后者是「大数减小数」：均值在 128 附近、方差只有几十时，两个百万量级的数相减会把有效位吃光。`03_layer-norm.cu` 的测试数据就是按这个刻意构造的。

**MHA 里 mask 为什么置 `-inf` 而不是 `0`？**
`exp(-inf) = 0`，softmax 后权重精确为 0；置 0 的话 `exp(0)=1`，被 mask 的位置反而会抢走注意力权重。

---

## 🐍 NumPy 参考实现

不依赖任何框架，纯手写，适合面试白板前先在本地跑通、把 shape 变换捋清楚。

| 文件 | 内容 |
|:---|:---|
| `attention.py` | `softmax` / `layer_norm` / `multi_head_attention`。含**向量化版 vs 三重循环直译版**的对拍、因果性验证、缩放因子随 `head_dim` 增长的演示 |
| `rope.py` | RoPE 的**两种配对约定**（交错对 / 前后半）各自实现并交叉验证，正交性与相对位置性质的数值验证 |

**`rope.py` 里那个坑值得单独记**：RoPE 有两种不等价的配对约定，很多资料混着讲——

- 约定 A「交错对」：配对 `(x0,x1), (x2,x3), ...`（原论文）
- 约定 B「前后半」：配对 `(x_i, x_{i+d/2}), ...`（GPT-NeoX / 多数 HF 模型，即 `rotate_half`）

两者只差一个固定的维度置换，能互相转换；但**把 B 的公式套在 A 的布局上，结果直接错**（实测误差 3.8）。`rope.py` 把这个错误用法也打出来做对照。

---

## 🎯 与 LeetGPU 的对应

平台按 Easy / Medium / Hard 分档，支持 **CUDA / Triton / CuTeDSL / Mojo** 四种模板，每题都能在网页里直接跑。哪些题和上面的 kernel 对应，写在表格的 `LeetGPU` 列里。

平台上的 softmax attention、reduction、GEMM(FP16)、top-k selection 等，和这几个 kernel 共享同一套「归约 + 分块」思路——先把这里的归约写法练熟，上去做会顺很多。

