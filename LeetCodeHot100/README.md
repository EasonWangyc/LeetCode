<div align="center">

# 🎯 LeetCode Hot 100

**按 17 个题型分类 · C++ 题解 + 一句话内核**

[![LeetCode](https://img.shields.io/badge/%E9%A2%98%E5%8D%95-LeetCode%20Hot%20100-FFA116?style=flat-square&logo=leetcode&logoColor=black)](https://leetcode.cn/problem-list/2cktkvj/)

<sub>刷题不是目的，能在面试里从题面条件推出解法才是。</sub>

</div>

---

## 🗺️ 学习路线

```mermaid
graph LR
    A["① 基础双指针<br/>哈希 · 双指针 · 滑动窗口 · 子串"] --> B["② 线性结构<br/>普通数组 · 矩阵 · 链表"]
    B --> C["③ 树与图<br/>二叉树 · 图论 · 回溯"]
    C --> D["④ 有序结构<br/>二分查找 · 栈 · 堆"]
    D --> E["⑤ 动态规划<br/>DP · 多维 DP"]
    E --> F["⑥ 技巧题"]

    classDef stage fill:#FFA116,stroke:#c47f0a,color:#000
    class A,B,C,D,E,F stage
```

> 思路笔记见 [summary.md](./summary.md)：每个分类包含「核心 / 模板 / 触发信号 / 逐题表」四块。

---

## 📚 题目索引

<details>
<summary><b>哈希</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 1 | 两数之和 | [1_twosum.cpp](./Hash/1_twosum.cpp) | `值 → 下标`，边遍历边插入 |
| 49 | 字母异位词分组 | [49_groupAnagrams.cpp](./Hash/49_groupAnagrams.cpp) | key 用「规范形式」：排序后的串 |
| 128 | 最长连续序列 | [128_longestConsecutive.cpp](./Hash/128_longestConsecutive.cpp) | 只从序列起点开始数，均摊 O(n) |

</details>

<details>
<summary><b>双指针</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 283 | 移动零 | [283_moveZeros.cpp](./TwoPointer/283_moveZeros.cpp) | 快慢指针，慢指针即非零元素个数 |
| 11 | 盛最多水的容器 | [11_maxArea.cpp](./TwoPointer/11_maxArea.cpp) | 每次移动较矮的一侧 |
| 15 | 三数之和 | [15_threeSum.cpp](./TwoPointer/15_threeSum.cpp) | 排序后固定 i，双指针收 j/k，两层去重 |
| 42 | 接雨水 | [42_trap.cpp](./TwoPointer/42_trap.cpp) | 短板决定水位，结算即将移动的一侧 |

</details>

<details>
<summary><b>滑动窗口</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 3 | 无重复字符的最长子串 | [3_lengthOfLongestSubstring.cpp](./SlidingWindow/3_lengthOfLongestSubstring.cpp) | 不合法就收缩，收缩到合法为止 |
| 438 | 找到字符串中所有字母异位词 | [438_findAnagrams.cpp](./SlidingWindow/438_findAnagrams.cpp) | 定长窗口 + 26 位计数比较 |

</details>

<details>
<summary><b>子串</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 560 | 和为 K 的子数组 | [560_subarraySum.cpp](./SubString/560_subarraySum.cpp) | 前缀和 + 哈希，key 是前缀和 |
| 239 | 滑动窗口最大值 | [239_maxSlidingWindow.cpp](./SubString/239_maxSlidingWindow.cpp) | 单调递减队列，队首即最大值 |
| 76 | 最小覆盖子串 | [76_minWindow.cpp](./SubString/76_minWindow.cpp) | 用 `valid` 计数避免整体比较 |

</details>

<details>
<summary><b>普通数组</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 53 | 最大子数组和 | [53_maxSubArray.cpp](./NormalArray/53_maxSubArray.cpp) | `f[i] = max(f[i-1] + x, x)` |
| 56 | 合并区间 | [56_mergeIntervals.cpp](./NormalArray/56_mergeIntervals.cpp) | 按左端点排序后一次扫描 |
| 189 | 轮转数组 | [189_rotate.cpp](./NormalArray/189_rotate.cpp) | 三次翻转 |
| 238 | 除自身以外数组的乘积 | [238_productExceptSelf.cpp](./NormalArray/238_productExceptSelf.cpp) | 前后缀分解，省掉除法 |
| 41 | 缺失的第一个正数 | [41_firstMissingPositive.cpp](./NormalArray/41_firstMissingPositive.cpp) | 原地哈希：把 `x` 放到下标 `x-1` |

</details>

<details>
<summary><b>矩阵</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 73 | 矩阵置零 | [73_setZeros.cpp](./Matrix/73_setZeros.cpp) | 用首行首列当标记数组 |
| 54 | 螺旋矩阵 | [54_spiralOrder.cpp](./Matrix/54_spiralOrder.cpp) | 四边界收缩 |
| 48 | 旋转图像 | [48_rotate.cpp](./Matrix/48_rotate.cpp) | 转置 + 左右翻转 |
| 240 | 搜索二维矩阵 II | [240_searchMatrix.cpp](./Matrix/240_searchMatrix.cpp) | 从右上角出发，一次排除一行/一列 |

</details>

<details>
<summary><b>链表</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 160 | 相交链表 | [getIntersectionNode.cpp](./ListNode/getIntersectionNode.cpp) | 双指针走完各自再走对方 |
| 206 | 反转链表 | [reverseList.cpp](./ListNode/reverseList.cpp) | `pre / cur / nxt` 三指针 |
| 234 | 回文链表 | [isPalindrome.cpp](./ListNode/isPalindrome.cpp) | 快慢指针找中点 + 反转后半 |
| 141 | 环形链表 | [141_hasCycle.cpp](./ListNode/141_hasCycle.cpp) | 快慢指针相遇即有环 |
| 142 | 环形链表 II | [142_detectCycle.cpp](./ListNode/142_detectCycle.cpp) | 相遇后一指针回头，同速再遇即入环点 |
| 21 | 合并两个有序链表 | [mergeTwoLists.cpp](./ListNode/mergeTwoLists.cpp) | 哨兵节点 + 双指针 |
| 2 | 两数相加 | [2_addTwoNumbers.cpp](./ListNode/2_addTwoNumbers.cpp) | 模拟竖式，带进位 |
| 19 | 删除链表的倒数第 N 个结点 | [removeNthFromEnd.cpp](./ListNode/removeNthFromEnd.cpp) | 快慢指针差 N 步 |
| 24 | 两两交换链表中的节点 | [swapPairs.cpp](./ListNode/swapPairs.cpp) | 哨兵 + 三个指针改向 |
| 25 | K 个一组翻转链表 | [reverseKGroup.cpp](./ListNode/reverseKGroup.cpp) | 先数够 k 个再翻转，接回前驱后继 |
| 138 | 随机链表的复制 | [138_copyRandomList.cpp](./ListNode/138_copyRandomList.cpp) | 哈希表存 `原节点 → 新节点` |
| 148 | 排序链表 | [sortList.cpp](./ListNode/sortList.cpp) | 归并排序：快慢指针找中点 + 合并 |
| 23 | 合并 K 个升序链表 | [mergeKLists.cpp](./ListNode/mergeKLists.cpp) | 分治两两合并，或优先队列 |
| 146 | LRU 缓存 | [codetop/146_LRU.cpp](../codetop/146_LRU.cpp) | 哈希表 + 双向链表 |

</details>

<details>
<summary><b>二叉树</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 94 | 二叉树的中序遍历 | [inorderTraversal.cpp](./TreeNode/inorderTraversal.cpp) | 递归 / 显式栈 |
| 104 | 二叉树的最大深度 | [maxDepth.cpp](./TreeNode/maxDepth.cpp) | `1 + max(左, 右)` |
| 226 | 翻转二叉树 | [invertTree.cpp](./TreeNode/invertTree.cpp) | 交换左右子树后递归 |
| 101 | 对称二叉树 | [isSymmetric.cpp](./TreeNode/isSymmetric.cpp) | 比较 `左.左 vs 右.右`、`左.右 vs 右.左` |
| 543 | 二叉树的直径 | [543_diameterofBinaryTree.cpp](./TreeNode/543_diameterofBinaryTree.cpp) | 边算深度边更新「左深 + 右深」 |
| 102 | 二叉树的层序遍历 | [levelorder.cpp](./TreeNode/levelorder.cpp) | BFS + 缓存 `q.size()` 分层 |
| 108 | 将有序数组转换为二叉搜索树 | [sortedArrayToBST.cpp](./TreeNode/sortedArrayToBST.cpp) | 取中点当根，递归左右 |
| 98 | 验证二叉搜索树 | [isValidBST.cpp](./TreeNode/isValidBST.cpp) | 传上下界，比只比父子更强 |
| 230 | 二叉搜索树中第 K 小的元素 | [KthSmallest.cpp](./TreeNode/KthSmallest.cpp) | 中序遍历的第 k 个 |
| 199 | 二叉树的右视图 | [rightSideView.cpp](./TreeNode/rightSideView.cpp) | BFS 每层最后一个 / DFS 记录首次到达的深度 |
| 114 | 二叉树展开为链表 | [114_faltten.cpp](./TreeNode/114_faltten.cpp) | 先序位置：左子树接到右，原右子树接最右 |
| 105 | 从前序与中序遍历序列构造二叉树 | [105_buildTree.cpp](./TreeNode/105_buildTree.cpp) | 前序定根，中序分左右区间 |
| 437 | 路径总和 III | | 前缀和 + 回溯（`sum - target` 查表） |
| 236 | 二叉树的最近公共祖先 | [codetop/236_lowestCommonAncestor.cpp](../codetop/236_lowestCommonAncestor.cpp) | 后序：左右都找到则当前即 LCA |
| 124 | 二叉树中的最大路径和 | [codetop/124_maxPathSum.cpp](../codetop/124_maxPathSum.cpp) | 后序返回「单边最大贡献」，全局更新「左 + 根 + 右」 |

</details>

<details>
<summary><b>图论</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 200 | 岛屿数量 | [200_numIslands.cpp](./GraphTheory/200_numIslands.cpp) | DFS 染色，grid 本身当 visited |
| 994 | 腐烂的橘子 | [994_OrangeRotting.cpp](./GraphTheory/994_OrangeRotting.cpp) | 多源 BFS，按层计分钟 |
| 207 | 课程表 | [207_canFinishCourse.cpp](./GraphTheory/207_canFinishCourse.cpp) | Kahn 拓扑排序判环 |
| 208 | 实现 Trie（前缀树） | [208_Trie.cpp](./GraphTheory/208_Trie.cpp) | 26 叉树 + `isEnd` 标记 |

</details>

<details>
<summary><b>回溯</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 46 | 全排列 | [46_fullpermute.cpp](./BackTrack/46_fullpermute.cpp) | `used` 数组，选完撤销 |
| 78 | 子集 | [78_subSets.cpp](./BackTrack/78_subSets.cpp) | 每个节点都收集，用 `start` 避免重复 |
| 17 | 电话号码的字母组合 | [17_letterCombinations.cpp](./BackTrack/17_letterCombinations.cpp) | 按位枚举候选字母 |
| 39 | 组合总和 | [39_combinationSum.cpp](./BackTrack/39_combinationSum.cpp) | 可重复选：递归传 `i` 而非 `i+1` |
| 22 | 括号生成 | [22_generateBracketPairs.cpp](./BackTrack/22_generateBracketPairs.cpp) | 左括号 < n 就能放，右括号 < 左括号就能放 |
| 79 | 单词搜索 | [79_searchWord.cpp](./BackTrack/79_searchWord.cpp) | 网格 DFS + 原地标记回溯 |
| 131 | 分割回文串 | [131_partition.cpp](./BackTrack/131_partition.cpp) | 按切割位置枚举，先判回文再递归 |
| 51 | N 皇后 | [51_solveNQueens.cpp](./BackTrack/51_solveNQueens.cpp) | 三个集合判列 / 主对角 / 副对角 |

</details>

<details>
<summary><b>二分查找</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 35 | 搜索插入位置 | [35_searchInsert.cpp](./BinarySearch/35_searchInsert.cpp) | 找第一个 `>= target` 的位置 |
| 74 | 搜索二维矩阵 | [74_searchMatrix.cpp](./BinarySearch/74_searchMatrix.cpp) | 行内二分，或把矩阵摊平成一维 |
| 34 | 在排序数组中查找元素的第一个和最后一个位置 | [34_searchRange.cpp](./BinarySearch/34_searchRange.cpp) | 两次二分：左边界 + 右边界 |
| 33 | 搜索旋转排序数组 | [33_searchRotate.cpp](./BinarySearch/33_searchRotate.cpp) | 每次必有一半有序，靠它判 target 在哪边 |
| 153 | 寻找旋转排序数组中的最小值 | [153_findMin.cpp](./BinarySearch/153_findMin.cpp) | 与右端点比较，找「下降点」 |
| 4 | 寻找两个正序数组的中位数 | [4_findMedianSortedArrays.cpp](./BinarySearch/4_findMedianSortedArrays.cpp) | 对短数组二分分割点，满足交叉不等式 |

</details>

<details>
<summary><b>栈</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 20 | 有效的括号 | [20_isValidbrackets.cpp](./Stack/20_isValidbrackets.cpp) | 左括号入栈，右括号匹配栈顶 |
| 394 | 字符串解码 | [394_decodestring.cpp](./Stack/394_decodestring.cpp) | 双栈存「重复次数 + 之前的串」 |
| 739 | 每日温度 | [739_dailyTemperatures.cpp](./Stack/739_dailyTemperatures.cpp) | 单调栈存下标，遇到更大值弹栈结算 |
| 155 | 最小栈 | | 辅助栈同步存当前最小值 |
| 84 | 柱状图中最大的矩形 | | 单调栈找左右第一个更矮的柱子 |

</details>

<details>
<summary><b>堆</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 215 | 数组中的第 K 个最大元素 | [codetop/215_findKthLargest.cpp](../codetop/215_findKthLargest.cpp) | 小顶堆保 k 个，或快速选择 |
| 347 | 前 K 个高频元素 | | 哈希计数 + 小顶堆按频次筛 |
| 295 | 数据流的中位数 | | 对顶堆：大顶存小半，小顶存大半 |

</details>

<details>
<summary><b>贪心算法</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 121 | 买卖股票的最佳时机 | [121_maxProfit.cpp](./GreedyAlgorithm/121_maxProfit.cpp) | 边扫边记历史最低价；**先算利润再更新最低价**，顺序保证不会同一天买卖 |
| 55 | 跳跃游戏 | [55_canJump.cpp](./GreedyAlgorithm/55_canJump.cpp) | 维护能到达的最远下标 `m`；一旦 `i > m` 就断档，返回 false |
| 45 | 跳跃游戏 II | [45_jump.cpp](./GreedyAlgorithm/45_jump.cpp) | 不真跳：逐格扫描，`cur` 是当前步的边界、`next` 是下一步能到的最远；`i == cur` 时 `ans++` 并把 `cur` 推到 `next` |
| 763 | 划分字母区间 | [763_partitionLabels.cpp](./GreedyAlgorithm/763_partitionLabels.cpp) | 先扫一遍记下每个字符最后出现的位置 `last[]`；再扫一遍用 `far` 扩右界，`i == far` 时就是一刀 |

</details>

<details>
<summary><b>动态规划</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 70 | 爬楼梯 | | `f[i] = f[i-1] + f[i-2]` |
| 118 | 杨辉三角 | | 逐行递推 |
| 198 | 打家劫舍 | [198_rob.cpp](./DynamicProgramming/198_rob.cpp) | `f[i] = max(f[i-1], f[i-2] + nums[i])` |
| 279 | 完全平方数 | | 完全背包，`f[i] = min(f[i - j²] + 1)` |
| 322 | 零钱兑换 | | 完全背包求最少硬币数 |
| 139 | 单词拆分 | | `f[i]` = 前 i 个字符能否由字典拼出 |
| 300 | 最长递增子序列 | [300_lengthOfLIS.cpp](./DynamicProgramming/300_lengthOfLIS.cpp) | `f[i]` 以 i 结尾的 LIS；贪心 + 二分可到 O(n log n) |
| 152 | 乘积最大子数组 | | 同时维护最大和最小（负数会翻转） |
| 416 | 分割等和子集 | | 0-1 背包，目标和为 `sum/2` |
| 32 | 最长有效括号 | | 栈存下标，或用 `f[i]` 记录以 i 结尾的长度 |

</details>

<details>
<summary><b>多维动态规划</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 62 | 不同路径 | | `f[i][j] = f[i-1][j] + f[i][j-1]` |
| 64 | 最小路径和 | | 同上取 min，注意首行首列初始化 |
| 5 | 最长回文子串 | [codetop/5_longestPalindrome.cpp](../codetop/5_longestPalindrome.cpp) | 区间 DP，按长度从小到大填 |
| 1143 | 最长公共子序列 | [codetop/1143_longestCommonSubsequence.cpp](../codetop/1143_longestCommonSubsequence.cpp) | 相等则左上 +1，否则取上/左较大者 |
| 72 | 编辑距离 | [72_minDistance.cpp](./MultiDimDynamicProgamming/72_minDistance.cpp) | 增 / 删 / 换三者取 min 再加 1 |

</details>

<details>
<summary><b>技巧</b></summary>

| # | 题目 | 题解 | 一句话内核 |
|:---:|:---|:---|:---|
| 136 | 只出现一次的数字 | | 全部异或，成对的抵消为 0 |
| 169 | 多数元素 | | 摩尔投票：不同则抵消 |
| 75 | 颜色分类 | | 三指针一次遍历（荷兰国旗） |
| 31 | 下一个排列 | | 从右找升序对，交换后反转后缀 |
| 287 | 寻找重复数 | | 值域当链表下标，转化为找环入口 |

</details>
