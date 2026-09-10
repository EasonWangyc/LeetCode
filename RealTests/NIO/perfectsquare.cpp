/*
给定一个正整数n。请计算满足下述条件的整数的个数:
- x是一个正整数。
- x! + 1  <= n。
- x! + 1为完全平方数

输入描述：输入一个整数n(1≤n≤10^18).
输出描述：输出一个整数，表示满足条件的x的个数。
*/
#include <iostream>
#include <cmath>
using namespace std;

bool isSquare(long long x){
    long long root = sqrt(x);
    return root * root == x;
}

int main(){
    long long n;
    cin >> n;
    int x = 1;
    int count = 0;
    long long fact = 1;
    while(true){
        fact *= x;
        if(fact + 1 > n) break;
        if(isSquare(fact + 1)) count++;
        x++;
    }
    cout << count << "\n";
    return 0;
}