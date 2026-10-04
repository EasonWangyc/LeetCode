/*
121. 买卖股票的最佳时机

给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int maxProfit(vector<int>& nums){
    int n = nums.size();
    int min_prize = nums[0];
    int ans = 0;
    for(int i = 1; i < n; i++){
        ans = max(ans, nums[i] - min_prize);
        min_prize = min(nums[i], min_prize);
    }
    return ans;
}

int main(){
    vector<int> nums = {2, 6, 1, 4, 10};
    cout << maxProfit(nums) << "\n";
    return 0;
}