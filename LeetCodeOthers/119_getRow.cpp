/*
119. 杨辉三角Ⅱ

给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> getRow(int rowIndex) {
    vector<vector<int>> ans(rowIndex + 1);
    for(int i = 0; i <= rowIndex; i++) {
        ans[i].resize(i + 1, 1);
        for(int j = 1; j < i; j++) ans[i][j] = ans[i - 1][j] + ans[i - 1][j - 1];
    }
    return ans[rowIndex];
}

int main() {
    vector<int> row = getRow(3);
    for(int num : row) cout << num << " ";
    cout << "\n";
    return 0;
}