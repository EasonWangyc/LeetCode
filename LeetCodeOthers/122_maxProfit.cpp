/*
122. 买卖股票的最佳时机Ⅱ
中等
相关标签
premium lock icon
相关企业
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。然而，你可以在 同一天 多次买卖该股票，但要确保你持有的股票不超过一股。

返回 你能获得的 最大 利润 。

思路：每天都有持股和不持股两个状态，每天可以买入、卖出、观望，通过这个构建转移方程。
设dp[i][0]、dp[i][1]分别为第i天不持股和持股
当天不持股：
1.昨天不持股，今天继续观望，dp[i-1][0]
2.昨天持股，今天卖出，dp[i-1][1]+prices[i]
两者取最大值
当天持股：
1.昨天不持股，今天买入，dp[i-1][0]-prices[i]
2.昨天持股，今天观望，dp[i-1][1]
两者取最大值

实际上当天的情况只取决于前一天，因此只需要两个变量
*/
#include <bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    // 初始化第一天持股和不持股
    int not_hold = 0;
    int hold = - prices[0];
    for(int i = 1; i < n; i++) {
        int new_not_hold = max(not_hold, hold + prices[i]);
        hold = max(not_hold - prices[i], hold);
        not_hold = new_not_hold;
    }
    return not_hold;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << maxProfit(prices) << "\n";
    return 0;
}