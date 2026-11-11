/*
37. 解数独

编写一个程序，通过填充空格来解决数独问题。

数独的解法需 遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
数独部分空格内已填入了数字，空白格用 '.' 表示。
*/
#include <bits/stdc++.h>
using namespace std;

class solution {
private:
    // 每行、每列、每九宫格各用一个九位二进制数表示数字是否被用过
    // 假设rows[0]=5=000000101，第0位和第2位为1，表示第一行已有1和3
    int rows[9] = {0};
    int cols[9] = {0};
    int boxes[9] = {0};
    // 表示需要填入的空格
    vector<pair<int, int>> spaces;
    
    bool dfs(vector<vector<char>>& board, int pos) {
        if(pos == spaces.size()) return true;
        auto [i, j] = spaces[pos];
        int box_index = (i / 3) * 3 + j / 3;
        for(int d = 0; d < 9; d++) {
            int mask = 1 << d;
            // & 按位与，全为1才是1
            if(!(rows[i] & mask) && !(cols[j] & mask) && !(boxes[box_index] & mask)) {
                // 填入数字
                rows[i] |= mask;
                cols[j] |= mask;
                boxes[box_index] |= mask;
                board[i][j] = d + '1';
                // 递归
                if(dfs(board, pos + 1)) return true;
                // 回溯
                // ^ 按位异或，用于撤销填入的数字
                /* 判断后先进行|运算
                rows[i] : 000000101  (已填 1, 3)
                | mask    : 000000010  (填入数字 2)
                ---------------------
                新状态  : 000000111  (现在 1, 2, 3 都被占用了)
                    回溯时进行^运算
                rows[i] : 000000111  (有 1, 2, 3)
                ^ mask    : 000000010  (撤销数字 2)
                ---------------------
                新状态  : 000000101  (数字 2 的开关被关掉了)
                */
                rows[i] ^= mask;
                cols[j] ^= mask;
                boxes[box_index] ^= mask;
                board[i][j] = '.';
            }
        }
        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(board[i][j] == '.') spaces.emplace_back(i, j);
                else {
                    int d = board[i][j] - '1';
                    int mask = 1 << d;
                    int box_index = (i / 3) * 3 + j / 3;
                    // | 表示按位或，只要有1就是1
                    rows[i] |= mask;
                    cols[j] |= mask;
                    boxes[box_index] |= mask;
                }
            }
        }
        dfs(board, 0);
    }
};

int main() {
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'}, 
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, 
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, 
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, 
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, 
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'}, 
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, 
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, 
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    solution s;
    s.solveSudoku(board);
    return 0;
}