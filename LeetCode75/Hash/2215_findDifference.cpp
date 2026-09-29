/*
2215. 找出两数组的不同

给你两个下标从 0 开始的整数数组 nums1 和 nums2 ，请你返回一个长度为 2 的列表 answer ，其中：

answer[0] 是 nums1 中所有 不 存在于 nums2 中的 不同 整数组成的列表。
answer[1] 是 nums2 中所有 不 存在于 nums1 中的 不同 整数组成的列表。
注意：列表中的整数可以按 任意 顺序返回。
*/
#include <unordered_set>
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2){
    // 快速转换成哈希集合
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> set2(nums2.begin(), nums2.end());
    vector<vector<int>> ans;
    vector<int> ans1, ans2;
    for(auto& x : set1){
        if(!set2.count(x)) ans1.push_back(x);
    }
    for(auto& y : set2){
        if(!set1.count(y)) ans2.push_back(y);
    }
    ans.push_back(ans1);
    ans.push_back(ans2);
    return ans;
}

int main(){
    vector<int> nums1 = {1, 2, 3, 3}, nums2 = {1, 1, 2, 2};
    vector<vector<int>> ans = findDifference(nums1, nums2);
    for(auto& a : ans){
        for(int x : a) cout << x << " ";
        cout << "\n";
    }
    return 0;
}