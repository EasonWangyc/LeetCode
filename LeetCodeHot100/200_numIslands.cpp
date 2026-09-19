/*
200. 岛屿数量

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
*/
#include <iostream>
#include <vector>
using namespace std;

// 染色
void dfs(vector<vector<char>>& grid, int row, int col){
    if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] == '0') return;
    grid[row][col] = '0';
    dfs(grid, row - 1, col);
    dfs(grid, row + 1, col);
    dfs(grid, row, col + 1);
    dfs(grid, row, col - 1);
}

int numIslands(vector<vector<char>>& grid){
    int n = grid.size();
    int m = grid[0].size();
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == '1'){
                ans++;
                dfs(grid, i, j);
            }
        }
    }
    return ans;
}

int main(){
    vector<vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                 {'1', '1', '0', '1', '0'},
                                 {'1', '1', '0', '0', '0'},
                                 {'0', '0', '0', '0', '1'},
                                };
    cout << numIslands(grid) << "\n";
    return 0;
}