/*
238. 除了自身以外数组的乘积

给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。
题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

思路：对于数组中任意位置i的元素，除自身以外的所有数字乘积，本质上可以拆成两部分的乘积，即前缀积×后缀积
*/
#include <vector>
#include <iostream>
using namespace std;

vector<int> productExceptSelf(vector<int>& nums){
    int n = nums.size();
    vector<int> suf(n);
    suf[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--) suf[i] = suf[i + 1] * nums[i + 1];
    int pre = 1;
    for(int i = 0; i < n; i++){
        suf[i] *= pre;
        pre *= nums[i];
    }
    return suf;
}

int main(){
    vector<int> nums = {1, 2, 3, 4};
    vector<int> ans = productExceptSelf(nums);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}