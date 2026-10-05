/*
31. 下一个排列

整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。

例如，arr = [1,2,3] ，以下这些都可以视作 arr 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1] 。
整数数组的 下一个排列 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 下一个排列 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。
类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。
而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。
给你一个整数数组 nums ，找出 nums 的下一个排列。

必须 原地 修改，只允许使用额外常数空间。

思路，以1 2 3 8 5 7 6 4 为例：
第一步：从右往左，找第一个破坏单调递减的数字，即5，764已经是其能组合出的最大数字，所以需要从右往左找到第一个满足nums[i] < nums[i+1]的数
第二步：从右往左找到第一个大于上面数字的数，即6，然后交换
第三步：将右侧的数字排列成升序，即6的右侧需要保证升序
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void nextPermutation(vector<int>& nums){
    int n = nums.size();
    int i = n - 2;
    while(i >= 0 && nums[i] >= nums[i + 1]) i--;
    // 特殊情况的全降序会返回-1，直接执行最后的reverse
    if(i >= 0){
        int j = n - 1;
        while(j >= 0 && nums[j] <= nums[i]) j--;
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}

int main(){
    vector<int> nums = {1, 2, 3, 8, 5, 7, 6 ,4};
    nextPermutation(nums);
    for(int num : nums) cout << num << " ";
    cout << "\n";
    return 0;
}