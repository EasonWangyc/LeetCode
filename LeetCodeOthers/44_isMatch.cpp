/*
44. 通配符匹配

给你一个输入字符串 (s) 和一个字符模式 (p) ，请你实现一个支持 '?' 和 '*' 匹配规则的通配符匹配：
'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符序列（包括空字符序列）。
判定匹配成功的充要条件是：字符模式必须能够 完全匹配 输入字符串（而不是部分匹配）。
*/
#include <bits/stdc++.h>
using namespace std;

bool isMatch(string s, string p) {
    int m = s.length(), n = p.length();
    vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));
    // 边界1
    f[0][0] = true;
    // 边界2
    for(int j = 1; j <= n; j++) {
        if(p[j - 1] == '*') f[0][j] = f[0][j - 1];
        else break;
    }
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(p[j - 1] == '?' || s[i - 1] == p[j - 1]) f[i][j] = f[i - 1][j - 1];
            // f[i][j-1]: * 匹配 0 个字符
            // f[i-1][j]: * 匹配 1 个或多个字符
            else if(p[j - 1] == '*') f[i][j] = f[i - 1][j] || f[i][j - 1];
        }
    }
    return f[m][n];
}

int main() {
    cout << boolalpha;
    cout << isMatch("", "?*") << "\n";
    cout << isMatch("sdhkh", "*2") << "\n";
    cout << isMatch("sd", "?d") << "\n";
    cout << isMatch("sadas", "sa*") << "\n";
    return 0;
}