/*
77. 组合

给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

你可以按 任何顺序 返回答案。
*/
#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<vector<int>>& ans, vector<int>& path, int index, int k) {
    if((int)path.size() == k) {
        ans.push_back(path);
        return;
    }
    // 剪枝：当前索引必须大于剩余需要选择的数量
    for(int j = index; j >= (int)(k - path.size()); j--) {
        path.push_back(j);
        backtrack(ans, path, j - 1, k);
        path.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> ans;
    vector<int> path;
    backtrack(ans, path, n, k);
    return ans;
}

int main() {
    vector<vector<int>> ans = combine(4, 2);
    for(auto &it : ans) {
        for(int num : it) cout << num << " ";
        cout << "\n";
    }
    return 0;
}