/*
746. 使用最小花费爬楼梯

给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。

一旦你支付此费用，即可选择向上爬 一个 或者 两个 台阶。

你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。

请你计算并返回达到楼梯顶部的最低花费，即最后一步之后的那个位置（下标 cost.length）。
*/
#include <bits/stdc++.h>
using namespace std;

int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    int a = 0;  // 从0出发
    int b = 0;  // 从1出发
    int c = 0;  // 初始化c
    for(int i = 2; i <= n; i++) {
        c = min(a + cost[i - 2], b + cost[i - 1]);
        a = b;
        b = c;
    }
    return c;
}

int main() {
    vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    cout << minCostClimbingStairs(cost) << "\n";
    return 0;
}