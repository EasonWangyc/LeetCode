/*
120. 三角形最小路径和

给定一个三角形 triangle ，找出自顶向下的最小路径和。

每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
*/
#include <bits/stdc++.h>
using namespace std;

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> ans(n);
    ans[0].resize(1);
    ans[0][0] = triangle[0][0];
    for(int i = 1; i < n; i++) {
        ans[i].resize(i + 1);
        ans[i][0] = ans[i - 1][0] + triangle[i][0];
        ans[i][i] = ans[i - 1][i - 1] + triangle[i][i];
        for(int j = 1; j < i; j++) ans[i][j] = min(ans[i - 1][j - 1], ans[i - 1][j]) + triangle[i][j];
    }
    return *min_element(ans[n - 1].begin(), ans[n - 1].end());
}

int main() {
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << minimumTotal(triangle) << "\n";
    return 0;
}