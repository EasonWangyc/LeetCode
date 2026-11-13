/*
50. Pow(x, n)

实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即x^n ）。

提示：
-100.0 < x < 100.0
-2^31 <= n <= 2^31-1
n 是一个整数
要么 x 不为零，要么 n > 0 。
-104 <= xn <= 104
*/
#include <bits/stdc++.h>
using namespace std;

// x^13 = x * x^4 * x^ 8
// 13 = 1101
double power(double x, long long n) {
    double res = 1;
    while(n) {
        if(n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

double myPow(double x, int n) {
    if(n >= 0) return power(x, n);
    return 1 / power(x, -1LL * n);
}

int main() {
    cout << myPow(2, 10) << "\n";
    cout << myPow(-3, -2) << "\n";
    cout << myPow(6, -4) << "\n";
    return 0;
}