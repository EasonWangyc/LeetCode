/*
6. Z 字形变换

将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

P   A   H   N
A P L S I I G
Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
*/
#include <bits/stdc++.h>
using namespace std;

string convert(string s, int numRows) {
    int n = s.length();
    if(n <= numRows || numRows <= 1) return s;
    vector<string> res(numRows);
    int flag = -1;
    int row = 0;
    for(char c : s) {
        res[row] += c;
        if(row == 0 || row == numRows - 1) flag = -flag;
        row += flag;
    }
    string ans = "";
    for(string s : res) ans += s;
    return ans;
}

int main() {
    string s = "PAYPALISHIRING";
    cout  << convert(s, 3) << " " << convert(s, 4) << "\n";
    return 0;
}