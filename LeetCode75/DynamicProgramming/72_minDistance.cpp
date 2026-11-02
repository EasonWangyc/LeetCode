/*
72. 编辑距离

给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
*/
#include <bits/stdc++.h>
using namespace std;

int minDistance(string a, string b) {
    int m = a.length(), n = b.length();
    vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
    for(int j = 1; j <= n; j++) f[0][j] = j;
    for(int i = 1; i <= m; i++) {
        f[i][0] = i;
        for(int j = 1; j <= n; j++){
            if(a[i - 1] == b[j - 1]) f[i][j] = f[i - 1][j - 1];
            else f[i][j] = min({f[i - 1][j], f[i][j - 1], f[i - 1][j - 1]}) + 1;
        }
    }
    return f[m][n];
}

int main() {
    string a = "horse", b = "ros";
    cout << minDistance(a, b) << "\n";
    return 0;
}