/*
90. 子集Ⅱ

给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的 子集（幂集）。

解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
*/
#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<int>& nums, vector<vector<int>>& ans, vector<int>& path, int index) {
    int n = nums.size();
    ans.push_back(path);
    for(int i = index; i < n; i++) {
        // 树层去重，横向层面当前元素不是第一个出现的相同元素
        if(i > index && nums[i] == nums[i - 1]) continue;
        path.push_back(nums[i]);
        backtrack(nums, ans, path, i + 1);
        path.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    vector<int> path;
    backtrack(nums, ans, path, 0);
    return ans;
}

int main() {
    vector<int> nums = {1, 2, 2};
    vector<vector<int>> ans = subsetsWithDup(nums);
    for(auto& it : ans) {
        for(int num : it) cout << num << " ";
        cout << "\n";
    }
    return 0;
}