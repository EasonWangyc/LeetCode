/*
643. 子数组最大平均数Ⅰ

给你一个由 n 个元素组成的整数数组 nums 和一个整数 k 。

请你找出平均数最大且 长度为 k 的连续子数组，并输出该最大平均数。

任何误差小于 10^-5 的答案都将被视为正确答案。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

double findMaxAverage(vector<int>& nums, int k){
    int max_value = INT_MIN;
    int cur = 0;
    for(int i = 0; i < nums.size(); i++){
        cur += nums[i];
        if(i < k - 1) continue;
        max_value = max(max_value, cur);
        cur -= nums[i - k + 1];
    }
    return (double) max_value / k;
}

int main(){
    vector<int> nums = {1, 12, -5, -6, 50, 3};
    cout << findMaxAverage(nums, 4) << "\n";
    return 0;
}