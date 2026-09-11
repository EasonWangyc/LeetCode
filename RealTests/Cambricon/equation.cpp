/*
小红拿到了一个奇怪的方程:a*√x+b*ln(x)=c。
请你帮小红求出的值。

输入描述：
第一行输入一个正整数t，代表询问次数。
接下来的t行，每行输入三个正整数a,b,c，代表一次询问。

输出描述：
t行，每行一个数表示方程的解。可以证明，该方程必然存在唯一的解。
如果你和正确答案的相对误差不超过10^-5，则认为你的答案正确。
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double equation(int a, int b, int c){
    double l = 0.0;
    double r = exp((double)c / b);
    while(r - l > 1e-10){
        double x = (l + r) / 2;
        double value = a * sqrt(x) + b * log(x);
        if(value < c) l = x;
        else r = x;
    }
    return (l + r) / 2;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int a, b, c;
        cin >> a >> b >> c;
        cout << fixed << setprecision(10) << equation(a, b, c) << "\n";
    }
    return 0;
}