/*
152. 乘积最大子数组

给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

请注意，一个只包含一个元素的数组的乘积是这个元素的值。
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

long long maxProduct(vector<long long>& nums){
    int n = nums.size();
    long long curMax = nums[0];
    long long curMin = nums[0];
    long long ans = nums[0];
    for(int i = 1; i < n; i++){
        long long x = nums[i];
        long long temp = curMax;
        curMax = max({temp * x, curMin * x, x});
        curMin = min({temp * x, curMin * x, x});
        ans = max(ans, curMax);
    }
    return ans;
}

int main(){
    vector<long long> nums = {2, 3, -2, 4};
    cout << maxProduct(nums) << "\n";
    return 0;
}