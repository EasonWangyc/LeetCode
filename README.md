<div align="center">

# 🗂️ 一个笨蛋的刷题记录

**C++/CUDA/Python · 分类归纳**

[![Hot 100](https://img.shields.io/badge/LeetCode-Hot%20100-FFA116?style=flat-square&logo=leetcode&logoColor=black)](./LeetCodeHot100/README.md) [![LeetCode 75](https://img.shields.io/badge/LeetCode-75-00AF9B?style=flat-square&logo=leetcode&logoColor=white)](./LeetCode75) [![codetop](https://img.shields.io/badge/codetop-%E9%AB%98%E9%A2%91%E6%A6%9C-6e4aff?style=flat-square)](./codetop)
[![LeetGPU](https://img.shields.io/badge/LeetGPU-CUDA%20Kernels-76B900?style=flat-square&logo=nvidia&logoColor=white)](./LeetGPU/README.md)
[![RealTests](https://img.shields.io/badge/%E7%9C%9F%E5%AE%9E%E7%AC%94%E8%AF%95-12%20%E5%AE%B6-3fb950?style=flat-square)](./RealTests)


</div>

---

## 📁 仓库地图

| 目录 | 是什么 | 组织方式 |
|:---|:---|:---|
| [`LeetCodeHot100/`](./LeetCodeHot100) | 主战场，Hot 100 全量 | 17 个题型分类，每个 `分类/题号_名字.cpp`；思路笔记见 [README](./LeetCodeHot100/README.md) 与 [summary.md](./LeetCodeHot100/summary.md) |
| [`LeetCode75/`](./LeetCode75) | 入门 75 题 | `Array&Substring` / `Hash` / `PrefixSum` / `SlidingWindow` / `TwoPointer` / `GraphTheory` |
| [`codetop/`](./codetop) | 面试高频题（codetop 榜单） | 平铺，`题号_名字.cpp` |
| [`RealTests/`](./RealTests) | 各公司真题 / 笔试题 | 按公司分目录 |
| [`LeetCodeOthers/`](./LeetCodeOthers) | 零散题目 | 平铺 |
| [`LeetGPU/`](./LeetGPU/README.md) | CUDA 手写算子 + LLM 组件（softmax / LayerNorm / RoPE / 多头注意力） | `cuda/` 可编译自测，`numpy/` 参考实现；文件名对齐 [LeetGPU](https://leetgpu.com/challenges) 题目 slug |

<details>
<summary><b>RealTests 的公司目录</b></summary>

| 公司 | 文件 |
|:---|:---|
| 字节 ByteDance | `WonderTree` · `maxKbyKSum` · `maxNumber` |
| 寒武纪 Cambricon | `equation` · `landmine` · `tree` |
| 大疆 DJI | `queue` |
| 乐鑫 Espressif | `minSlope` · `sevenGame` |
| 华为 Huawei | `XORTree` · `browser` · `monster` · `pcb` · `stingtoseptum` · `version` |
| 联想 Lenovo | `monotonicarrays` · `remove` |
| 蔚来 NIO | `Bezout` · `perfectsquare` |
| Sharpa | `findKlargest` |
| vivo | `button` · `encryption` · `maxBoundaryNumber` |
| 文远知行 WeRide | `Problem` · `uniqueFrequency` · `zombie` |
| 小鹏 Xiaopeng | `mergeIntervals` |
| 科大讯飞 iFLYTEK | `prime` · `waterLevel` |

<sub>目录名不带题号，文件名即题目内容；这些是笔试原题，多数不是 LeetCode 原题。</sub>

</details>

---

## 🏷️ 文件命名约定

```text
分类目录/题号_小驼峰.cpp      # 例：Hash/49_groupAnagrams.cpp
```

- **带题号前缀**：排序、检索、和 `summary.md` 的表格对得上
- **函数名一律用 LeetCode 官方签名**（`orangesRotting`、`flatten`、`reverseWords`）—— 面试手写靠的是肌肉记忆，练习惯的名字没意义
- **`int main()` 只放一组最小样例**，够本地跑通就行

---

## ⚙️ 编译运行

每个 `.cpp` 自包含（内置 `struct` 定义 + `main()`），不需要额外头文件。

```bash
# 编译运行
g++ -std=c++17 -O2 -o /tmp/sol LeetCodeHot100/Hash/1_twosum.cpp && /tmp/sol

# 带调试符号（查越界 / 未定义行为）
g++ -std=c++17 -g -fsanitize=address,undefined -o /tmp/sol LeetCodeHot100/TwoPointer/42_trap.cpp && /tmp/sol
```

> `output/` 和 `codetop/test.cpp` 已加入 `.gitignore`，都是本地编译/草稿产物。

`LeetGPU/` 下的 `.cu` 用 nvcc 编译，同样自包含（内置 CPU 参考实现 + 自测）：

```bash
nvcc -arch=sm_89 -O2 -o /tmp/k LeetGPU/cuda/05_multi-head-self-attention.cu && /tmp/k
```

详见 [LeetGPU/README.md](./LeetGPU/README.md)。
