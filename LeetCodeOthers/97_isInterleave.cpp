/*
97. 交错字符串

给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错 组成的。

两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
交错 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
注意：a + b 意味着字符串 a 和 b 连接。
*/
#include <bits/stdc++.h>
using namespace std;

bool isInterleave(string s1, string s2, string s3){
    int m = s1.length(), n = s2.length(), l = s3.length();
    if(l != m + n) return false;
    vector<vector<bool>> f(m + 1, vector<bool>(n + 1));
    // f[i][j]表示，s1的前i个字符和s2的前j个字符能否交替拼成s3的前i+j个字符
    f[0][0] = true;
    for(int j = 0; j < n; j++){
        f[0][j + 1] = f[0][j] && s2[j] == s3[j];
    }
    for(int i = 0; i < m; i++){
        f[i + 1][0] = f[i][0] && s1[i] == s3[i];
        for(int j = 0; j < n; j++){
            f[i + 1][j + 1] = f[i][j + 1] && s3[i + j + 1] == s1[i] ||
                              f[i + 1][j] && s3[i + j + 1] == s2[j];
        }
    }
    return f[m][n];
}

int main(){
    string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
    cout << boolalpha << isInterleave(s1, s2, s3) << "\n";
    return 0;
}