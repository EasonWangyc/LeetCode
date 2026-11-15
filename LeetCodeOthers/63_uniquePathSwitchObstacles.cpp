/*
63. 不同路径Ⅱ

给定一个 m x n 的整数数组 grid。一个机器人初始位于 左上角（即 grid[0][0]）。机器人尝试移动到 右下角（即 grid[m - 1][n - 1]）。机器人每次只能向下或者向右移动一步。

网格中的障碍物和空位置分别用 1 和 0 来表示。机器人的移动路径中不能包含 任何 有障碍物的方格。

返回机器人能够到达右下角的不同路径数量。

测试用例保证答案小于等于 2 * 10^9。
*/
#include <bits/stdc++.h>
using namespace std;

int uniquePathSwitchObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> f(m, vector<int>(n, 0));
    bool alive_col = true, alive_row = true;
    if(obstacleGrid[0][0] == 1) {
        f[0][0] = 0;
        alive_col = false;
        alive_row = false;
    }else f[0][0] = 1;
    for(int j = 1; j < n; j++) {
        if(alive_col == false || obstacleGrid[0][j] == 1) {
            alive_col = false;
            f[0][j] = 0;
        }else f[0][j] = 1;
    }
    for(int i = 1; i < m; i++) {
        if(alive_row == false || obstacleGrid[i][0] == 1) {
            alive_row = false;
            f[i][0] = 0;
        }else f[i][0] = 1;
        for(int j = 1; j < n; j++) {
            if(obstacleGrid[i][j] == 1) f[i][j] = 0;
            else f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    }
    return f[m - 1][n - 1];
}

int main() {
    vector<vector<int>> obstacleGrid = {{0, 1}, {0, 0}};
    cout << uniquePathSwitchObstacles(obstacleGrid) << "\n";
    return 0;
}