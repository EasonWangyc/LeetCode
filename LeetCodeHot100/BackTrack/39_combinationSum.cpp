/*
39. 组合总和

给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void backtrack(vector<int>& candidates, int target, int sum, int startIndex, vector<int>& path, vector<vector<int>>& ans){
    if(sum == target){
        ans.push_back(path);
        return;
    }
    int n = candidates.size();
    for(int i = startIndex; i < n; i++){
        if(candidates[i] + sum > target) break;
        path.push_back(candidates[i]);
        backtrack(candidates, target, sum + candidates[i], i, path, ans);
        path.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target){
    vector<vector<int>> ans;
    vector<int> path;
    sort(candidates.begin(), candidates.end());
    backtrack(candidates, target, 0, 0, path, ans);
    return ans;
}

int main(){
    vector<int> candidates = {2, 3, 6, 7};
    vector<vector<int>> ans = combinationSum(candidates, 7);
    for(auto& nums : ans){
        for(auto& num : nums) cout << num << " ";
        cout << "\t";
    }
    cout << "\n";
    return 0;
}