/*
714. 买卖股票的最佳时机含手续费

给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格；整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
*/
#include <bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    // 初始化第一天持股和不持股
    int not_hold = 0;
    int hold = - prices[0] - fee;
    for(int i = 1; i < n; i++) {
        int new_not_hold = max(not_hold, hold + prices[i]);
        hold = max(not_hold - prices[i] - fee, hold);
        not_hold = new_not_hold;
    }
    return not_hold;
}

int main() {
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    cout << maxProfit(prices, 2) << "\n";
    return 0;
}