/*
8. 字符串转换整数 (atoi)

请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数。

函数 myAtoi(string s) 的算法如下：

空格：读入字符串并丢弃无用的前导空格（" "）
符号：检查下一个字符（假设还未到字符末尾）为 '-' 还是 '+'。如果两者都不存在，则假定结果为正。
转换：通过跳过前置零来读取该整数，直到遇到非数字字符或到达字符串的结尾。如果没有读取数字，则结果为0。
舍入：如果整数数超过 32 位有符号整数范围 [−2^31,  2^31 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −2^31 的整数应该被舍入为 −2^31 ，大于 2^31 − 1 的整数应该被舍入为 2^31 − 1 。
返回整数作为最终结果。
*/
#include <bits/stdc++.h>
using namespace std;

int myAtoi(string s) {
    int i = 0;
    int n = s.length();
    while(i < n && s[i] == ' ') i++;
    if(i == n) return 0;
    int sign = 1;
    if(s[i] == '+' || s[i] == '-') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    int ans = 0;
    while(i < n && isdigit(s[i])) {
        int digit = s[i] - '0';
        // -2^31也包含在>7的情况内
        if(ans > INT_MAX / 10 || (ans == INT_MAX / 10 && digit > 7)){
            return (sign == 1) ? INT_MAX : INT_MIN;
        }
        ans = ans * 10 + digit;
        i++;
    }
    return sign * ans;
}

int main() {
    cout << myAtoi("-42") << " " << myAtoi("987 with word") << " " << myAtoi("WORD with 1001") << " " << myAtoi("-2083072489279848964") << " " << myAtoi("2147483648") << "\n";
    return 0;
}