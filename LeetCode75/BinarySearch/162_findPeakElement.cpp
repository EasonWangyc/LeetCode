/*
162. 寻找峰值

峰值元素是指其值严格大于左右相邻值的元素。

给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞ 。

你必须实现时间复杂度为 O(log n) 的算法来解决此问题。
*/
#include <bits/stdc++.h>
using namespace std;

// 核心是比较nums[i]和nums[i+1]的大小关系，如果nums[mid]>nums[mid+1]说明左侧有峰值，反之亦然
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    int l = 0, r = n - 2;   // 防止mid+1越界
    while(l <= r){
        int mid = l + (r - l) / 2;
        if(nums[mid] > nums[mid + 1]) r = mid - 1;
        else l = mid + 1;
    }
    return l;               // 循环结束条件l==r+1
}

int main() {
    vector<int> nums = {1, 2, 3, 1};
    cout << findPeakElement(nums) << "\n";
    return 0;
}