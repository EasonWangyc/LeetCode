/*
78. 子集

给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
*/
#include <vector>
#include <iostream>
using namespace std;

void backtrack(vector<int>& nums, vector<int>& path, int startIndex, vector<vector<int>>& ans){
    ans.push_back(path);
    int n = nums.size();
    for(int i = startIndex; i < n; i++){
        path.push_back(nums[i]);
        backtrack(nums, path, i + 1, ans);
        path.pop_back();
    }
}

vector<vector<int>> subSets(vector<int>& nums){
    vector<int> path;
    vector<vector<int>> ans;
    backtrack(nums, path, 0, ans);
    return ans;
}

int main(){
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> ans = subSets(nums);
    for(auto& nums : ans){
        for(auto& num : nums) cout << num << " ";
        cout << "\t";
    }
    cout << "\n";
    return 0;
}