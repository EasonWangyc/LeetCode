/*
40. 组合总和Ⅱ

给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用 一次 。

注意：解集不能包含重复的组合。 
*/
#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<int>& candidates, vector<vector<int>>& ans, vector<int>& path, int sum, int target, int index) {
    if(sum == target){
        ans.push_back(path);
        return;
    }
    for(int i = index; i < (int)candidates.size(); i++) {
        // 剪枝1
        if(sum + candidates[i] > target) break;
        // 剪枝2：同一层中的两个相邻相同数
        if(i > index && candidates[i] == candidates[i - 1]) continue;
        path.push_back(candidates[i]);
        backtrack(candidates, ans, path, sum + candidates[i], target, i + 1);
        path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> path;
    sort(candidates.begin(), candidates.end());
    backtrack(candidates, ans, path, 0, target, 0);
    return ans;
}

int main() {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    vector<vector<int>> ans = combinationSum2(candidates, 8);
    for(auto& v : ans) {
        for(int num : v) cout << num << " ";
        cout << "\n";
    }
    return 0;
}