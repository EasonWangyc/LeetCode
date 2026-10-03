/*
35. 搜索插入位置

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 O(log n) 的算法。
*/
#include <vector>
#include <iostream>
using namespace std;

int searchInsert(vector<int>& nums, int target){
    int l = 0, r = nums.size() - 1;
    while(l <= r){
        int mid = (r - l) / 2 + l;
        if(nums[mid] == target) return mid;
        else if(nums[mid] > target) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

int main(){
    vector<int> nums = {1, 2, 3, 6};
    cout << searchInsert(nums, 3) << searchInsert(nums, 5) << searchInsert(nums, 7) << "\n";
    return 0;
}