/*
62. 不同路径

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？
*/
#include <bits/stdc++.h>
using namespace std;

int uniquePath(int m, int n) {
    vector<vector<int>> f(m, vector<int>(n, 1));
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) f[i][j] = f[i - 1][j] + f[i][j - 1];
    }
    return f[m - 1][n - 1];
}

int main() {
    cout << uniquePath(3, 7) << "\n";
    return 0;
}