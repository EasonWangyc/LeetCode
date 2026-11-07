/*
10. 正则表达式匹配

给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素，不能单独出现
返回一个布尔值，表示匹配是否覆盖整个输入字符串（而非部分）。

考虑p[j-1]
1.如果p[j-1]不是'*'，只能严格匹配，只能s[i-1]==p[j-1]或p[j-1]=='.'，所以f[i][j]=f[i-1][j-1]否则false
2.如果p[j-1]是'*'，由于可以匹配零个或多个前面的那一个元素，分类讨论：
2-A.匹配零次，相当于丢弃'p[j-2]*'的组合，此时f[i][j]=f[i][j-2]，例子是"a"与"ab*"是匹配的
2-B.匹配一次，s[i-1]必须与p[j-2]匹配上，此时s[i-1]==p[j-2]或p[j-2]=='.'，然后f[i][j]=f[i-1][j]
*/
#include <bits/stdc++.h>
using namespace std;

bool matches(string& s, string& p, int i, int j) {
    if(i == 0) return false;
    if(p[j - 1] == '.') return true;
    return s[i - 1] == p[j - 1];
}

bool isMatch(string s, string p) {
    int m = s.length(), n = p.length();
    // f[i][j]表示s[0, ..., i-1]与p[0, ..., j-1]是否匹配
    vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));
    // 边界条件1，空串与空串
    f[0][0] = true;
    // 边界条件2，空串与非空模式，只有形如"a*b*c*"才能匹配
    for(int j = 1; j <= n; j++){
        if(p[j - 1] == '*') f[0][j] = f[0][j - 2];
    }
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(p[j - 1] == '*') {
                f[i][j] = f[i][j - 2] || (matches(s, p, i, j - 1) && f[i - 1][j]);
            }else {
                if(matches(s, p, i, j)) f[i][j] = f[i - 1][j - 1];
            }
        }
    }
    return f[m][n];
}

int main() {
    cout << boolalpha;
    cout << isMatch("aaaabc", "a*b.") << "\n";
    cout << isMatch("", "a*") << "\n";
    cout << isMatch("sakjdl", ".*.*k") << "\n";
    return 0;
}