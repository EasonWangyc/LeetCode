/*
1318. 或运算的最小翻转次数

给你三个正整数 a、b 和 c。

你可以对 a 和 b 的二进制表示进行位翻转操作，返回能够使按位或运算 a OR b == c  成立的最小翻转次数。

「位翻转操作」是指将一个数的二进制表示任何单个位上的 1 变成 0 或者 0 变成 1 。
*/
#include <bits/stdc++.h>
using namespace std;

int countBits(int n) {
    int count = 0;
    // Brian Kernighan算法
    while(n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

// 先计算a|b，然后对c异或，计算不同位，特殊情况是c该位为0且a和b该位均为1，此时需要翻转2次
int minFlips(int a, int b, int c) {
    int diff = (a | b) ^ c;
    int double_flips = (a & b) & ~c; // 按位取反
    return countBits(diff) + countBits(double_flips);
}

int main() {
    int a = 4, b = 2, c = 7;
    cout << minFlips(a, b, c) << "\n";
    return 0;
}