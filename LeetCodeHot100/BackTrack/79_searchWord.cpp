/*
79. 单词搜索

给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
*/
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool backtrack(vector<vector<char>>& board, const string& word, int k, int x, int y){
    int m = board.size(), n = board[0].size();
    if(x < 0 || x >= m || y >= n || y < 0 || board[x][y] != word[k]) return false;
    if((long unsigned int)k == word.size() - 1) return true;
    char tmp = board[x][y];
    board[x][y] = '#';
    bool res = backtrack(board, word, k + 1, x + 1, y) ||
               backtrack(board, word, k + 1, x - 1, y) ||
               backtrack(board, word, k + 1, x, y + 1) ||
               backtrack(board, word, k + 1, x, y - 1);
    board[x][y] = tmp;
    return res;
}

bool searchWord(vector<vector<char>>& board, string word){
    int m = board.size(), n = board[0].size();
    // 剪枝1：统计board中字符出现次数，若word中某个字符在board中出现次数不足直接返回false
    unordered_map<char, int> mp;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            mp[board[i][j]]++;
        }
    }
    for(char c : word){
        if(--mp[c] < 0) return false;
    }
    // 剪枝2：反转首尾频次
    if(mp[word.front()] > mp[word.back()]) reverse(word.begin(), word.end());
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(backtrack(board, word, 0, i, j)) return true;
        }
    }
    return false;
}

int main(){
    vector<vector<char>> board = {{'A', 'B', 'C', 'E'},
                                  {'S', 'F', 'C', 'S'},
                                  {'A', 'D', 'E', 'E'}};
    string word = "ABCCSE";
    cout << boolalpha << searchWord(board, word) << "\n";
    return 0;
}