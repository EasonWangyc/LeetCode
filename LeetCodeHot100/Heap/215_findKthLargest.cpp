/*
215. 数组中的第K个最大元素

给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
*/
#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>
using namespace std;

/* 优先队列做法，时间复杂度O(nlogk)
int findKthLargest(vector<int>& nums, int k){
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for(int x : nums){
        minHeap.push(x);
        if(minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}
*/

// 原地快速选择，非快速排序
int findKthLargest(vector<int>& nums, int k){
    int n = nums.size();
    int target = n - k;
    int l = 0, r = n - 1;
    while(l <= r){
        int pivot_idx = l + rand() % (r - l + 1);
        int pivot = nums[pivot_idx];
        // 划分为[<pivot] [==pivot] [>pivot]三部分
        int lt = l;     // nums[l .. lt-1] < pivot
        int gt = r;     // nums[gt+1 .. r] > pivot
        int i = l;      // nums[lt .. gt] == pivot
        // [ l ... lt-1 ] [ lt ... i-1 ] [ i ... gt ] [ gt+1 ... r ]
        // i从lt开始遍历到gt，放置好所有未知元素
        while(i <= gt){
            if(nums[i] == pivot) i++;
            else if(nums[i] < pivot){
                // lt指向等于区域的第一个元素，交换就是把小于pivot的元素扔进小于区域，所以需要lt++
                swap(nums[i], nums[lt]);
                i++;
                lt++;
            }else {
                // 由于从左往右遍历，[i, gt]之间的区域都是未知元素，交换后不能i++
                swap(nums[i], nums[gt]);
                gt--;
            }
        }
        if(target < lt) r = lt - 1;
        else if(target > lt) l = gt + 1;
        else return nums[lt];
    }
    return -1;
}

int main(){
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << findKthLargest(nums, 2) << "\n";
    return 0;
}