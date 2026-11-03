/*
435. 无重叠区间

给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。

注意 只在一点上接触的区间是 不重叠的。例如 [1, 2] 和 [2, 3] 是不重叠的。
*/
#include <bits/stdc++.h>
using namespace std;

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    int right = intervals[0][1];
    int n = intervals.size();
    int count = 0;
    for(int i = 1; i < n; i++) {
        if(right > intervals[i][0]) {
            count++;
            // 贪心：尽可能让右端点小
            right = min(right, intervals[i][1]);
        }
        else right = intervals[i][1];
    }
    return count;
}

int main() {
    vector<vector<int>> intervals = {{1, 100}, {1, 2}, {2, 3}, {3, 4}};
    cout << eraseOverlapIntervals(intervals) << "\n";
    return 0;
}