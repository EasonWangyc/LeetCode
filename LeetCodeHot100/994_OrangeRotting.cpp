/*
994. 腐烂的橘子

在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：
值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。
每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

思路：
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int OrangeRotting(vector<vector<int>>& grid){
    int m = grid.size(), n = grid[0].size();
    int minutes = 0;
    int fresh = 0;
    queue<pair<int, int>> q;
    int directions[4][2] = {{1, 0}, {-1 , 0}, {0, 1}, {0, -1}};
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 2) q.push({i, j});
            else if(grid[i][j] == 1) fresh++;
        }
    }
    if(fresh == 0) return 0;
    while(!q.empty() && fresh != 0){
        minutes++;
        int size = q.size();
        for(int i = 0; i < size; i++){
            auto [r, c] = q.front();
            q.pop();
            for(auto& d : directions){
                int rc = r + d[0], cc = c + d[1];
                if(rc < m && rc >= 0 && cc < n && cc >=0 && grid[rc][cc] == 1){
                    grid[rc][cc] = 2;
                    fresh--;
                    q.push({rc, cc});
                }
            }
        } 
    }
    return fresh == 0 ? minutes : -1;
}

int main(){
    vector<vector<int>> grid = {{2, 1, 1}, {1 , 1, 0}, {0, 1, 1}};
    cout << OrangeRotting(grid) << "\n";
    return 0;
}