/*
52. N 皇后 II

n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。
*/
#include <bits/stdc++.h>
using namespace std;

void backtrack(int n, int row, vector<bool>& usedCol, vector<bool>& usedDiag1, vector<bool>& usedDiag2, int& ans) {
    if(row == n) {
        ans++;
        return;
    }
    for(int col = 0; col < n; col++) {
        if(usedCol[col] || usedDiag1[row + col] ||usedDiag2[row - col + n]) continue;
        usedCol[col] = usedDiag1[row + col] = usedDiag2[row - col + n] = true;
        backtrack(n, row + 1, usedCol, usedDiag1, usedDiag2, ans);
        usedCol[col] = usedDiag1[row + col] = usedDiag2[row - col + n] = false;
    }
}

int totalNQueens(int n) {
    int ans = 0;
    vector<bool> usedCol(n, false), usedDiag1(2 * n, false), usedDiag2(2 * n, false);
    backtrack(n, 0, usedCol, usedDiag1, usedDiag2, ans);
    return ans;
}

int main() {
    cout << totalNQueens(4) << " " << totalNQueens(7) << "\n";
    return 0;
}