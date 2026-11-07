/*
7. 整数反转

给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 [−2^31,  2^31 − 1] ，就返回 0。

假设环境不允许存储 64 位整数（有符号或无符号）。 
*/
#include <bits/stdc++.h>
using namespace std;

int reverse(int x) {
    int ans = 0;
    while(x) {
        int pop = x % 10; // 负数取模也会保留符号
        x /= 10;
        // INT_MAX $= 2^{31} - 1 = \mathbf{2147483647}
        // $INT_MIN $= -2^{31} = \mathbf{-2147483648}$
        if(ans > INT_MAX / 10 || (ans == INT_MAX && pop > 7)) return 0;
        if(ans < INT_MIN / 10 || (ans == INT_MIN && pop < -8)) return 0;
        ans = ans * 10 + pop;
    }
    return ans;
}

int main() {
    cout << reverse(INT_MIN / 10) << "\n";
    return 0;
}