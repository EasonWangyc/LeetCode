/*
33. 搜索旋转排序数组

整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 向左旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 下标 3 上向左旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
*/
#include <iostream>
#include <vector>
using namespace std;

int searchRotate(vector<int>& nums, int target){
    int l = 0, r = nums.size() - 1;
    while(l <= r){
        int mid = l + (r - l) / 2;
        int x = nums[mid];
        if(x == target) return mid;
        if(x > nums[r]){
            // [l, mid]升序
            if(nums[l] <= target && x > target) r = mid - 1;
            else l = mid + 1;
        }else{
            // [mid, r]升序
            if(nums[r] >= target && x < target) l = mid + 1;
            else r = mid - 1;
        }
    }
    return -1;
}

int main(){
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    cout << searchRotate(nums, 3) << "\n";
    return 0;
}