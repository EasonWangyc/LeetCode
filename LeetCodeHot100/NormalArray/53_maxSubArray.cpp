/*
53. 最大子数组和

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组是数组中的一个连续部分。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int maxSubarray(vector<int>& nums){
    int ans = INT8_MIN;
    int s = 0;
    int s_min = 0;
    for(int num : nums){
        s += num;
        ans = max(ans, s - s_min);
        s_min = min(s, s_min);
    }
    return ans;
}

int main(){
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, 5, -4};
    cout << maxSubarray(nums) << "\n";
    return 0;
}