/*
198. 打家劫舍

你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
*/
#include <bits/stdc++.h>
using namespace std;

int rob(vector<int>& nums) {
    int n = nums.size();
    // dp[i]表示偷到第i-1个房屋时能够获得的最高金额，即dp[i]对应nums[i-1]
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = nums[0];
    for(int i = 2; i <= n; i++) {
        dp[i] = max(dp[i - 2] + nums[i - 1], dp[i - 1]);
    }
    return dp[n];
}

int main(){
    vector<int> nums = {4, 2, 5, 4};
    cout << rob(nums) << "\n";
    return 0;
}