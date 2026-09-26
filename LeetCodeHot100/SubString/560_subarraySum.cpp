/*
560. 和为 K 的子数组

给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
子数组是数组中元素的连续非空序列。

思路：前缀和 + 哈希表
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int subarraySum(vector<int>& nums, int k){
    int n = nums.size();
    vector<int> s(n + 1);
    for(int i = 0; i < n; i++) s[i + 1] = s[i] + nums[i];
    unordered_map<int, int> mp;
    int ans = 0;
    for(int sj : s){
        if(mp.count(sj - k)) ans += mp[sj - k];
        mp[sj]++;
    }
    return ans;
}

int main(){
    vector<int> nums = {1, 2, 3};
    cout << subarraySum(nums, 3) << "\n";
    return 0;
}