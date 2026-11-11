/*
29. 两数相除

给你两个整数，被除数 dividend 和除数 divisor。将两数相除，要求 不使用 乘法、除法和取余运算。

整数除法应该向零截断，也就是截去（truncate）其小数部分。例如，8.345 将被截断为 8 ，-2.7335 将被截断至 -2 。

返回被除数 dividend 除以除数 divisor 得到的 商 。

注意：假设我们的环境只能存储 32 位 有符号整数，其数值范围是 [−2^31,  2^31 − 1] 。本题中，如果商 严格大于 2^31 − 1 ，则返回 2^31 − 1 ；如果商 严格小于 -2^31 ，则返回 -2^31 。
*/
#include <bits/stdc++.h>
using namespace std;

int divide(int dividend, int divisor) {
    if(divisor == 1) return dividend;
    if(divisor == -1) {
        if(dividend == INT_MIN) return INT_MAX;
        return -dividend;
    }
    bool isNegative = (dividend > 0) ^ (divisor > 0);
    // 统一转成负数处理
    int a = dividend > 0 ? -dividend : dividend;
    int b = divisor > 0 ? -divisor : divisor;
    int ans = 0;
    while(a <= b) {
        int cur_b = b;
        int count = -1;
        while(cur_b >= (INT_MAX >> 1) && a <= (cur_b << 1)) {
            cur_b <<= 1;
            count <<= 1;
        }
        a -= cur_b;
        ans += count;
    }
    return isNegative ? ans : -ans;
}

int main() {
    int dividend = 10, divisor = 3;
    cout << divide(10, 3) << "\n";
    return 0;
}