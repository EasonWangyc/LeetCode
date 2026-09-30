/*
41. 缺失的第一个正数

给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。

思路：想象成排座位，遍历数组，将正整数n放在n-1处，处理完后判断即可。
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int firstMissingPositive(vector<int>& nums){
    int n = nums.size();
    for(int i = 0; i < n; i++){
        // 交换回来的可能是正整数，需要继续交换，所以用while
        while(nums[i] > 0 && nums[i] < n && nums[i] != nums[nums[i] - 1]){
            int j = nums[i] - 1;
            swap(nums[i], nums[j]);
        }
    }
    for(int i = 0; i < n; i++){
        if(nums[i] != i + 1) return i + 1;
    }
    return n + 1;
}

int main(){
    vector<int> nums = {3, 4, -1, 1};
    cout << firstMissingPositive(nums) << "\n";
    return 0;
}