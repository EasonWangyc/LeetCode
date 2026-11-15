/*
65. 有效数字

给定一个字符串 s ，返回 s 是否是一个 有效数字。

例如，下面的都是有效数字："2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"，而接下来的不是："abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"。

一般的，一个 有效数字 可以用以下的规则之一定义：

一个 整数 后面跟着一个 可选指数。
一个 小数 后面跟着一个 可选指数。
一个 整数 定义为一个 可选符号 '-' 或 '+' 后面跟着 数字。

一个 小数 定义为一个 可选符号 '-' 或 '+' 后面跟着下述规则：

数字 后跟着一个 小数点 .。
数字 后跟着一个 小数点 . 再跟着 数位。
一个 小数点 . 后跟着 数位。
指数 定义为指数符号 'e' 或 'E'，后面跟着一个 整数。

数字 定义为一个或多个数位。
*/
#include <bits/stdc++.h>
using namespace std;

bool isNumber(string s) {
    int n = s.length();
    int i = 0;
    if(i < n && (s[i] == '+' || s[i] == '-')) i++;
    // 指数符号之前
    bool has_dot = false;
    bool has_digit = false;
    while(i < n && s[i] != 'e' && s[i] != 'E') {
        if(s[i] == '.'){
            if(has_dot) return false;
            has_dot = true;
        }else if(s[i] >= '0' && s[i] <= '9') has_digit = true;
        else return false;
        i++;
    }
    if (i < n && (s[i] == 'e' || s[i] == 'E')) {
        if (!has_digit) return false; // 指数前面必须有数字
        i++; // 跳过 'e' 或 'E'

        // 指数部分必须是整数，且不能为空
        if (i < n && (s[i] == '+' || s[i] == '-')) i++;

        bool has_exp_digit = false;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            has_exp_digit = true;
            i++;
        }
        if (!has_exp_digit) return false; // 'e' 后面必须有数字
    }
    return i == n && has_digit;
}

int main() {
    cout << boolalpha << isNumber("-.9") << " " << isNumber("95a54e53") << "\n";
    return 0;
}