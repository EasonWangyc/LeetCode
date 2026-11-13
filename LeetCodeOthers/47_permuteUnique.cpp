/*
47. 全排列Ⅱ

给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
*/
#include <bits/stdc++.h>
using namespace std;

void dfs(vector<int>& nums, vector<vector<int>>& ans, vector<int>& path, vector<int>& on_path, int i) {
    int n = nums.size();
    if(i == n) {
        ans.push_back(path);
        return;
    }
    for(int j = 0; j < n; j++) {
        // 如果 nums[j] 已填入排列，continue
        // 如果 nums[j] 和前一个数 nums[j-1] 相等，且 nums[j-1] 没填入排列，continue
        if(on_path[j] || (j > 0 && nums[j] == nums[j - 1] && !on_path[j - 1])) continue;
        path[i] = nums[j];
        on_path[j] = true;
        dfs(nums, ans, path, on_path, i + 1);
        on_path[j] = false;
        // 这里path没有pop_back是因为path的长度固定，直接赋值path[i]
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<int> path(n);
    vector<int> on_path(n); // on_path[j]表示nums[j]是否已经填入
    vector<vector<int>> ans;
    dfs(nums, ans, path, on_path, 0);
    return ans;
}

int main() {
    vector<int> nums = {1, 1, 2};
    vector<vector<int>> ans = permuteUnique(nums);
    for(auto& it : ans) {
        for(int num : it) cout << num << " ";
        cout << "\n";
    }
    return 0;
}