/*
1137. 第 N 个泰波那契数

泰波那契序列 Tn 定义如下： 

T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2

给你整数 n，请返回第 n 个泰波那契数 Tn 的值。

提示：
0 <= n <= 37
答案保证是一个 32 位整数，即 answer <= 2^31 - 1。

直接使用公式进行递归，大量重复计算，会超时
*/
#include <bits/stdc++.h>
using namespace std;

int tribonacci(int n) {
    if(n == 0) return 0;
    if(n <= 2) return 1;
    int a = 0, b = 1, c = 1;
    for(int i = 3; i <= n; i++) {
        int d = a + b + c;
        a = b;
        b = c;
        c = d;
    }
    return c;
}

int main() {
    cout << tribonacci(4) << " " << tribonacci(37) << "\n";
    return 0;
}