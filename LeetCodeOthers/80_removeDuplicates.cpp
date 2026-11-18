/*
80. 删除有序数组中的重复项Ⅱ

给定一个按 非递减顺序 排列的整数数组 nums，请你 原地 删除部分重复元素，使得每个不同的元素 最多出现两次。元素的 相对顺序 应保持 不变。

由于在某些语言中无法改变数组的长度，因此必须将结果放在数组 nums 的前半部分。更准确地说，如果删除重复元素后有 k 个元素，那么 nums 的前 k 个元素应该保存最终结果。前 k 个元素之后的内容无关紧要。

将最终结果放入 nums 的前 k 个位置后，返回 k。

不要 为另一个数组分配额外空间。你必须使用 O(1) 的额外内存，通过 原地 修改输入数组 来完成此操作。

自定义判题：

判题程序将使用以下代码测试你的解答：

int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的预期答案

int k = removeDuplicates(nums); // 调用你的实现

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
如果所有断言都通过，那么你的解答将被 接受。
*/
#include <bits/stdc++.h>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    // vector当作栈，如果当前元素等于栈顶下方那个数，即倒数第二个数
    // 由于数组非递减，前两个数一定满足要求
    int stack_size = 2;
    for(int i = 2; i < n; i++) {
        if(nums[i] != nums[stack_size - 2]) nums[stack_size++] = nums[i];
    }
    // 可能有一个元素的情况
    return min(n, stack_size);
}

int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    cout << removeDuplicates(nums) << "\n";
    return 0;
}