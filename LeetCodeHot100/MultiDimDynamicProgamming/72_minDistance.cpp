/*
72. 编辑距离

给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数。
你可以对一个单词进行如下三种操作：
插入一个字符
删除一个字符
替换一个字符

思路：用一个二维数组f[i][j]表示word1[0,...,i-1]变化为word2[0,...,j-1]的最少操作数
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int minDistance(string word1, string word2){
    int n = word1.length(), m = word2.length();
    vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
    for(int j = 0; j < m; j++) f[0][j + 1] = j + 1;
    for(int i = 0; i < n; i++){
        f[i + 1][0] = i + 1;
        for(int j = 0; j < m; j++){
            if(word1[i] == word2[j]) f[i + 1][j + 1] = f[i][j];
            else f[i + 1][j + 1] = min({f[i][j], f[i + 1][j], f[i][j + 1]}) + 1;
        } 
    }
    return f[n][m];
}

int main(){
    string word1 = "horse", word2 = "ros";
    cout << minDistance(word1, word2) << "\n";
    return 0;
}