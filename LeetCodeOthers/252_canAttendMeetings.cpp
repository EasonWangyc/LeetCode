/*
252. 会议室

给定一个由会议时间区间组成的数组 intervals，其中 intervals[i] = [starti, endi]，请你判断一个人是否能够参加这里面的全部会议。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool canAttendMeetings(vector<vector<int>>& intervals){
    sort(intervals.begin(), intervals.end());
    int n = intervals.size();
    for(int i = 1; i < n; i++){
        if(intervals[i - 1][1] > intervals[i][0]) return false;
    }
    return true;
}