/*
56. 合并区间

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals){
    if(intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    int n = intervals.size();
    for(int i = 1; i < n; i++){
        if(intervals[i][0] <= merged.back()[1]){
            merged.back()[1] = max(intervals[i][1], merged.back()[1]);
        }else merged.push_back(intervals[i]);
    }
    return merged;
}

int main(){
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> ans = mergeIntervals(intervals);
    for(auto& nums : ans){
        for(int num : nums) cout << num << " ";
        cout << "\t";
    }
    cout << "\n";
    return 0;
}