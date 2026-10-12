/*
2352. 相等行列对

给你一个下标从 0 开始、大小为 n x n 的整数矩阵 grid ，返回满足 Ri 行和 Cj 列相等的行列对 (Ri, Cj) 的数目。

如果行和列以相同的顺序包含相同的元素（即相等的数组），则认为二者是相等的。
*/
#include <vector>
#include <map>
#include <iostream>
using namespace std;

int equalPairs(vector<vector<int>>& grid) {
    int n = grid.size();
    map<vector<int>, int> row_cnt;

    // 1. 统计每一行出现的频次
    for (const auto& row : grid) {
        row_cnt[row]++;
    }

    int ans = 0;
    // 2. 构造每一列并在 map 中查询
    for (int j = 0; j < n; ++j) {
        vector<int> col(n);
        for (int i = 0; i < n; ++i) {
            col[i] = grid[i][j];
        }
        if (row_cnt.count(col)) {
            ans += row_cnt[col];
        }
    }

    return ans;
}

int main(){
    vector<vector<int>> grid = {{3, 1, 2, 2},
                                {1, 4, 4, 5},
                                {2, 4, 2, 2},
                                {2, 4, 2, 2}};
    cout << equalPairs(grid) << "\n";
    return 0;
}