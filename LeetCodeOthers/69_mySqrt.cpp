/*
69. x 的平方根 

给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。
*/
#include <bits/stdc++.h>
using namespace std;

int mySqrt(int x) {
    // 实际测试46341就overflow，根据题意最大就是46340，对应平方为INT_MAX
    int left = 0, right = min(x, 46340);
    while(left <= right) {
        int mid = (left + right) / 2;
        if(mid * mid <= x) left = mid + 1;
        else right = mid - 1;
    }
    return right;
}

int main() {
    cout << mySqrt(INT_MAX) << "\n";
    return 0;
}