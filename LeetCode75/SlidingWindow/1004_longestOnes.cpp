/*
1004. 最大连续1的个数Ⅲ

给定一个二进制数组 nums 和一个整数 k，假设最多可以翻转 k 个 0 ，则返回执行操作后 数组中连续 1 的最大个数 。

思路：可以转化为“寻找一个最长的子数组，使得该子数组内部0的个数不超过k。”
*/
#include <iostream>
#include <vector>
using namespace std;

int longestOnes(vector<int>& nums, int k){
    int count = 0, ans = 0, left = 0;
    for(int right = 0; right < nums.size(); right++){
        count += 1 - nums[right];
        // 只要0的个数小于k就能满足全连续1
        while(count > k) count -= 1 - nums[left++];
        ans = max(ans, right - left + 1);
    }
    return ans;
}

int main(){
    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    cout << longestOnes(nums, 2) << "\n";
    return 0;
}