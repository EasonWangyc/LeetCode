/*
115. 不同的子序列

给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数。

测试用例保证结果在 32 位有符号整数范围内。
*/
#include <bits/stdc++.h>
using namespace std;

int numDistinct(string s, string t) {
    int m = s.length(), n = t.length();
    if(m < n) return 0;
    // 用f[i+1][j+1]表示s[0...i]的所有子序列中t[0...j]出现的个数
    vector f(m + 1, vector<unsigned int>(n + 1));
    f[0][0] = 1;
    for(int i = 1; i <= m; i++) {
        f[i][0] = 1;
        // 下界：s剩余m-i个字符，t剩余n-j个字符，m-i>=n-j，即j>=n-m+i
        // 上界：不可能超出i的长度
        for(int j = max(n - m + i, 1); j <= min(i, n); j++) {
            // 不使用s[i-1]
            f[i][j] = f[i - 1][j];
            if(s[i - 1] == t[j - 1]) f[i][j] += f[i - 1][ j -1];
        }
    }
    return f[m][n];
}

int main() {
    string s = "babgbag", t = "bag";
    cout << numDistinct(s, t) << "\n";
    return 0;
}