/*
67. 二进制求和

给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。
*/
#include <bits/stdc++.h>
using namespace std;

string addBinary(string a, string b) {
    string ans = "";
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;

    // 从右往左逐位相加，直到两个字符串都走完且没有剩余进位
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        
        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }

        // 当前位的值为 sum % 2，进位为 sum / 2
        carry = sum / 2;
        ans.push_back((sum % 2) + '0');
    }

    // 因为是从低位往高位 push 的，最后需要反转字符串
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    cout << addBinary("110", "101") << "\n";
    return 0;
}