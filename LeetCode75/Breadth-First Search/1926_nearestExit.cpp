/*
1926. 迷宫中离入口最近的出口

给你一个 m x n 的迷宫矩阵 maze （下标从 0 开始），矩阵中有空格子（用 '.' 表示）和墙（用 '+' 表示）。同时给你迷宫的入口 entrance ，用 entrance = [entrancerow, entrancecol] 表示你一开始所在格子的行和列。

每一步操作，你可以往 上，下，左 或者 右 移动一个格子。你不能进入墙所在的格子，你也不能离开迷宫。你的目标是找到离 entrance 最近 的出口。出口 的含义是 maze 边界 上的 空格子。entrance 格子 不算 出口。

请你返回从 entrance 到最近出口的最短路径的 步数 ，如果不存在这样的路径，请你返回 -1 。
*/
#include <bits/stdc++.h>
using namespace std;

static const vector<pair<int, int>> DIRS = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
    int m = maze.size(), n = maze[0].size();
    int ex = entrance[0], ey = entrance[1];
    maze[ex][ey] = 0;   // 访问标记
    vector<pair<int, int>> q = {{ex, ey}};
    for(int ans = 1; !q.empty(); ans++){
        auto tmp = move(q); // 使用move使得q为空
        for(auto& [i, j] : tmp){
            for(auto& [dx, dy] : DIRS){
                int x = i + dx, y = j + dy;
                if(x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == '.'){
                    if(x == 0 || x == m - 1 || y == 0 || y == n - 1) return ans;
                    maze[x][y] = 0;
                    q.emplace_back(x, y);
                }
            }
        }
    }
    return -1;
}

int main(){
    vector<vector<char>> maze = {{'+', '+', '.', '+'},
                                 {'.', '.', '.', '+'},
                                 {'+', '+', '+', '.'}};
    vector<int> entrance = {1, 2};
    cout << nearestExit(maze, entrance) << "\n";
    return 0;
}