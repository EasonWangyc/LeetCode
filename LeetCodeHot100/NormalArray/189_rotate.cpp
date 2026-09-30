/*
189. 轮转数组

给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

思路：反转再反转。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void rotate(vector<int>& nums, int k){
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

int main(){
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    rotate(nums, 3);
    for(auto& x : nums) cout << x << " ";
    cout << "\n";
    return 0;
}