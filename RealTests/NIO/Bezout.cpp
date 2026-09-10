/*
给定四个整数x,y,l,r。我们称一个整数n能被“用x和y表示”，当且仅当存在整数a,b使得n=ax+by。
请你统计区间[l,r]中有多少个整数可以被“用x和y表示”。
说明:a,b可以为任意整数(包含负数与0);x,y为正整数。

输入描述：一行输入四个整数
每个测试文件均包含多组测试数据。第一行输入一个整数T(1≤T≤10^5)代表数据组数，每组测试数据描述如下:
x,y,l,r (1≤x,y≤10^9,-10^18≤1≤r≤10^18).

输出描述：对于每组数据，输出一个整数，表示区间[l,r]中可表示整数的个数。

思路：裴蜀定理（Bézout 定理），因为 (a,b) 可以取任意整数，所以$$ n=ax+by $$能够表示的所有整数，恰好是$$ gcd(x,y) $$的整数倍。
*/
#include <iostream>
#include <numeric>
using namespace std;

long long floorDiv(long long a, long long b){
    long long q = a / b;
    if(a % b != 0 && a < 0) q--;
    return q;
}

int main(){
    int T = 0;
    cin >> T;
    while(T--){
        long long x, y, l, r;
        cin >> x >> y >> l >> r;
        long long g = gcd(x, y);
        long long ans = floorDiv(r, g) - floorDiv(l - 1, g);
        cout << ans << "\n";
    }
    return 0;
}