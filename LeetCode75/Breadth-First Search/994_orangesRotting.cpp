/*
994. 腐烂的橘子

在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：

值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。
每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。
*/
#include <bits/stdc++.h>
using namespace std;

int orangesRotting(vector<vector<int>>& grid) {
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int m = grid.size(), n = grid[0].size();
    int fresh = 0, minutes = 0;
    vector<pair<int, int>> q;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 1) fresh++;
            if(grid[i][j] == 2) q.emplace_back(i, j);
        }
    }
    while(fresh != 0 && !q.empty()){
        minutes++;
        vector<pair<int, int>> next;
        for(auto& [i, j] : q){
            for(auto& [dx, dy] : directions){
                int x = i + dx, y = j + dy;
                if(x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1){
                    fresh--;
                    grid[x][y] = 2;
                    next.emplace_back(x, y);
                }
            }
        }
        q = move(next);
    }
    return fresh == 0 ? minutes : -1;
}

int main(){
    vector<vector<int>> grid = {{2, 1, 1}, {1 , 1, 0}, {0, 1, 1}};
    cout << orangesRotting(grid) << "\n";
    return 0;
}