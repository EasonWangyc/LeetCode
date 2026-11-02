/*
790. 多米诺和托米诺平铺

有两种形状的瓷砖：一种是 2 x 1 的多米诺形，另一种是形如 "L" 的托米诺形。两种形状都可以旋转。

给定整数 n ，返回可以平铺 2 x n 的面板的方法的数量。返回对 10^9 + 7 取模 的值。

平铺指的是每个正方形都必须有瓷砖覆盖。两个平铺不同，当且仅当面板上有四个方向上的相邻单元中的两个，使得恰好有一个平铺有一个瓷砖占据两个正方形。

考虑第i列，有四种情况：
1.全满，记为f[i][0]
2.上面格子被覆盖，下面没有，记为f[i][1]
3.下面格子被覆盖，上面没有，记为f[i][2]，由于对称性，f[i][1]=f[i][2]
4.全空，此时去考虑i-1列

通过推导，有f[i][0]=f[i-1][0]+f[i-2][0]+2*f[i-1][1]和f[i][1]=f[i-2][0]+f[i-1][1]
得到f[i][0]=2*f[i-1][0]+f[i-3][0]
*/
#include <bits/stdc++.h>
using namespace std;

int numTilings(int n) {
    if(n == 1) return 1;
    if(n == 2) return 2;
    if(n == 3) return 5;
    const int MOD = 1e9 +7;
    long long a = 1;
    long long b = 2;
    long long c = 5;
    for(int i = 4; i <= n; i++){
        long long d = (2 * c + a) % MOD;
        a = b;
        b = c;
        c = d;
    }
    return c;
}

int main() {
    cout << numTilings(10) << "\n";
    return 0;
}