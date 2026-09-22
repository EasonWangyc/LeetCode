/*
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

示例：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

思路：回溯法，通过递归构建全排列，用一个bool数组记录每个数字是否被使用，每次选择一个未使用的数字加入当前排列，直到排列长度等于数组长度，将其加入结果集，然后回溯撤销选择，尝试其他可能。
*/
#include <iostream>
#include <vector>
using namespace std;

void backtrack(const vector<int>& nums, vector<bool> & used, vector<vector<int>>& ans, vector<int>& path){
    if(path.size() == nums.size()){
        ans.push_back(path);
        return;
    }
    for(int i = 0; i < nums.size(); i++){
        if(used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        backtrack(nums, used, ans, path);
        path.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> fullpermute(vector<int>& nums){
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    backtrack(nums, used, ans, path);
    return ans;
}

int main(){
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> ans = fullpermute(nums);
    for(int i = 0; i < ans.size(); i++){
        for(int j = 0; j < ans[0].size(); j++){
            cout << ans[i][j] << "";
        }
        cout << "\n";
    }
    return 0;
}