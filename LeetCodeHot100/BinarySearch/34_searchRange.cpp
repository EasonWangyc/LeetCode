/*
34. 在排序数组中查找元素的第一个和最后一个位置

给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
*/
#include <iostream>
#include <vector>
using namespace std;

int lower_bound_index(vector<int>& nums, int target){
    int l = 0, r = nums.size() - 1;
    while(l <= r){
        int mid = l + (r - l) / 2;
        if(nums[mid] >= target) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

vector<int> searchRange(vector<int>& nums, int target){
    int start = lower_bound_index(nums, target);
    int n = nums.size();
    if(start == n || nums[start] != target) return {-1, -1};
    int end = lower_bound_index(nums, target + 1) - 1;
    return {start, end};
}

int main(){
    vector<int> nums = {5, 6, 7, 7, 8, 10};
    vector<int> ans = searchRange(nums, 8);
    for(auto& num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}