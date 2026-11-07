/*
9. 回文数

给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。

回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
*/
#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(int x) {
    if(x < 0 || (x % 10 == 0 && x != 0)) return false;
    int reverseNumber = 0;
    while(x > reverseNumber) {
        reverseNumber = reverseNumber * 10 + x % 10;
        x /= 10;
    }
    // 1221和12321
    return x == reverseNumber || x == reverseNumber / 10;
}

int main() {
    cout << boolalpha << isPalindrome(12321) << "\n";
    return 0;
}