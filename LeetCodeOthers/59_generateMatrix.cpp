/*
59. 螺旋矩阵Ⅱ

给你一个正整数 n ，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> ans(n, vector<int>(n, 0));
    int u = 0, d = n - 1, l = 0, r = n - 1;
    int number = 1;
    while(number <= n * n) {
        for(int i = l; i <= r; i++) ans[u][i] = number++;
        u++;
        for(int i = u; i <= d; i++) ans[i][r] = number++;
        r--;
        for(int i = r; i >= l; i--) ans[d][i] = number++;
        d--;
        for(int i = d; i >= u; i--) ans[i][l] = number++;
        l++;
    }
    return ans;
}

int main() {
    vector<vector<int>> ans = generateMatrix(3);
    for(const auto& v : ans) {
        for(int num : v) cout << num << " ";
        cout << "\n";
    }
    return 0;
}