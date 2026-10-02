/*
51. N 皇后

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

思路：将递归深度直接对应为行号，回溯时每次进入下一行，每次判断列、主对角线、副对角线即可，用三个bool数组标记，遍历列索引，对于列，usedCol[i]不能为true，对于两条对角线，分别有行列之差为定值，范围[-n+1, n-1]，加n到[1, 2n-1]，和行列之和为定值，范围[0, 2n-2]，初始化两个2n大小的数组，backtrack()中先判断path长度是否为n并返回，然后判断当前是否满足三个数组对应元素均为false，只要有一个满足就continue，走到下面说明当前节点可以放置，更新path和标记，回溯进入下一个row，然后恢复原始值和标记。
*/
#include <vector>
#include <iostream>
using namespace std;

void backtrack(int n, int row, vector<string>& path,
               vector<bool> usedCol,
               vector<bool> usedDiag1,
               vector<bool> usedDiag2,
               vector<vector<string>>& ans){
    if(row == n){
        ans.push_back(path);
        return;
    }
    for(int col = 0; col < n; col++){
        // 只有有一个不满足就continue
        if(usedCol[col] || usedDiag1[row + col] ||usedDiag2[row - col + n]) continue;
        // 放置皇后同时更新标记
        path[row][col] = 'Q';
        usedCol[col] = usedDiag1[row + col] = usedDiag2[row - col + n] = true;
        backtrack(n, row + 1, path, usedCol, usedDiag1, usedDiag2, ans);
        // 对称回溯
        path[row][col] = '.';
        usedCol[col] = usedDiag1[row + col] = usedDiag2[row - col + n] = false;
    }
}

vector<vector<string>> solveNQueens(int n){
    vector<vector<string>> ans;
    vector<string> path(n, string(n, '.'));
    vector<bool> usedCol(n, false), usedDiag1(2 * n, false), usedDiag2(2 * n, false);
    backtrack(n, 0, path, usedCol, usedDiag1, usedDiag2, ans);
    return ans;
}

int main(){
    vector<vector<string>> ans = solveNQueens(4);
    for(auto& ss : ans){
        for(auto& s : ss) cout << s << "\n";
        cout << "\n";
    }
    cout << "\n";
    return 0;
}