/*
无序数组中找到第K大的数。

优化：两路切分-->三路切分，详见：LeetCodeHot100/Heap/215_findKthLargest.cpp
*/
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int partition(vector<int>& nums, int left, int right){
    int i = left + rand()%(right - left + 1);
    int pivot = nums[i];
    swap(nums[i], nums[left]);
    i = left + 1;
    int j = right;
    while(true){
        while(i <= j && nums[i] < pivot) i++;
        while(i <= j && nums[i] > pivot) j--;
        if(i >= j) break;
        swap(nums[i], nums[j]);
        i++;
        j--;
    }
    swap(nums[left], nums[j]);
    return j;
}

int quickselect(vector<int>& nums, int left, int right, int K){
    int p = partition(nums, left, right);
    if(p == K) return nums[p];
    else if(p > K) return quickselect(nums, left, p - 1, K);
    else return quickselect(nums, p + 1, right, K);
}

int main(){
    vector<int> nums = {3, 5, 2, 56, 40, 639, 9};
    int K = 2;
    int n = nums.size();
    srand(time(NULL));
    cout << quickselect(nums, 0, n - 1, n - K) << "\n";
    return 0;
}