/*
1143. 最长公共子序列

给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
*/
#include <bits/stdc++.h>
using namespace std;

int longestCommonSubsequence(string a, string b) {
    int m = a.length(), n = b.length();
    vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(a[i - 1] == b[j - 1]) f[i][j] = f[i - 1][j - 1] + 1;
            else f[i][j] = max(f[i -1][j], f[i][j - 1]);
        }
    }
    return f[m][n];
}

int main() {
    string a = "abcde", b = "ace";
    cout << longestCommonSubsequence(a, b) << "\n";
    return 0;
}