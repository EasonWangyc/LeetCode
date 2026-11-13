/*
57. 插入区间

给你一个 无重叠的 ，按照区间起始端点排序的区间列表 intervals，其中 intervals[i] = [starti, endi] 表示第 i 个区间的开始和结束，并且 intervals 按照 starti 升序排列。同样给定一个区间 newInterval = [start, end] 表示另一个区间的开始和结束。

如果两个区间 至少 共享一个点，则认为它们是重叠的。

在 intervals 中插入区间 newInterval，使得 intervals 依然按照 starti 升序排列，且区间之间不重叠（如果有必要的话，可以合并区间）。

返回插入之后的 intervals。

注意 你不需要原地修改 intervals。你可以创建一个新数组然后返回它。
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    int left = newInterval[0], right = newInterval[1];
    vector<vector<int>> ans;
    // placed 是一个状态标记，表示合并后的新区间 {left, right} 是否已经被放入结果数组 ans 中
    bool placed = false;
    for(const auto& interval : intervals) {
        if(interval[0] > right) {
            // 在循环中途插入，用placed标记保证只插入一次
            if(!placed) {
                ans.push_back({left, right});
                placed = true;
            }
            ans.push_back(interval);
        }else if(interval[1] < left) ans.push_back(interval);
        else {
            left = min(interval[0], left);
            right = max(interval[1], right);
        }
    }
    // 循环结束插入
    if(!placed) ans.push_back({left, right});
    return ans;
}

int main() {
    vector<vector<int>> intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> newInterval = {4, 8};
    vector<vector<int>> ans = insert(intervals, newInterval);
    for(const auto& interval : ans) {
        cout << interval[0] << " " << interval[1] << "\n";
    }
    return 0;
}