/*
416. 分割等和子集

给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
*/
#include <vector>
#include <iostream>
using namespace std;

bool canPartition(vector<int>& nums){
    int n = nums.size();
    int sum = 0;
    for(int num : nums) sum+= num;
    if(sum % 2) return false;
    int target = sum / 2;
    vector<bool> dp(target + 1, false); // dp[j]表示是否能找到子数组的和为j
    dp[0] = true;
    for(int i = 0; i < n; i++){
        // 倒序遍历防止数字被重复使用
        for(int j = target; j >= nums[i]; j--){
            if(dp[j - nums[i]]) dp[j] = true;
        }
        if(dp[target]) return true;
    }
    return false;
}

int main(){
    vector<int> nums = {1, 5, 11, 5};
    cout << boolalpha << canPartition(nums) << "\n";
    return 0;
}