/*
901. 股票价格跨度

设计一种算法，收集某支股票的每日价格报价，并返回该股票当前日期的 价格跨度。

股票在某一天的 价格跨度 是指：从当天开始向前，连续的股票价格小于或等于当天价格的最大天数。

例如，如果股票过去四天的价格为 [7,2,1,2]，今天的价格为 2，那么今天的价格跨度为 4，因为从今天开始向前，有连续 4 天的股票价格小于或等于 2。
同样，如果股票过去四天的价格为 [7,34,1,2]，今天的价格为 8，那么今天的价格跨度为 3，因为从今天开始向前，有连续 3 天的股票价格小于或等于 8。
实现 StockSpanner 类：

StockSpanner() 初始化该类的对象。
int next(int price) 给定今天的股票价格 price，返回今天股票价格的 价格跨度。
*/
#include <bits/stdc++.h>
using namespace std;

class StockSpanner {
private:
    stack<pair<int, int>> st;
    int cur_day = 0;
public:
    StockSpanner() {
        st.emplace(-1, INT_MAX);
    }

    int next(int price) {
        // 本质上是找price前的第一个大于price数，因此比price先加入且小于price的数不可能作为后续查找的依据
        while(price >= st.top().second) {
            st.pop();
        }
        int ans = cur_day - st.top().first;
        st.emplace(cur_day, price);
        cur_day++;
        return ans;
    }
};

int main() {
    StockSpanner ss;
    cout << ss.next(100) << "\n";
    cout << ss.next(80) << "\n";
    cout << ss.next(60) << "\n";
    cout << ss.next(70) << "\n";
    cout << ss.next(60) << "\n";
    cout << ss.next(75) << "\n";
    cout << ss.next(85) << "\n";
    return 0;
}