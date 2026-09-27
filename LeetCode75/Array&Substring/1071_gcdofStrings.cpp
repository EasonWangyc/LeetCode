/*
1071. 字符串的最大公因子

对于字符串 s 和 t，只有在 s = t + t + t + ... + t + t（t 自身连接 1 次或多次）时，我们才认定 “t 能除尽 s”。
给定两个字符串 str1 和 str2 。返回 最长字符串 x，要求满足 x 能除尽 str1 且 x 能除尽 str2 。
*/
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

string gcdofStrings(string str1, string str2){
    if((str1 + str2) != (str2 + str1)) return "";
    // 字符串长度的最大公因数
    return str1.substr(0, gcd(str1.length(), str2.length()));
}

int main(){
    string str1 = "ABCABC", str2 = "ABC";
    cout << gcdofStrings(str1, str2) << "\n";
    return 0;
}