/*
43. 字符串相乘

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。
*/
#include <bits/stdc++.h>
using namespace std;

string multiply(string num1, string num2) {
    int m = num1.length(), n = num2.length();
    vector<int> ans(m + n, 0);
    for(int i = m - 1; i >= 0; i--) {
        for(int j = n - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + ans[i + j + 1];
            ans[i + j + 1] = sum % 10;
            ans[i + j] += sum / 10;
        }
    }
    string res;
    for(int num : ans) {
        if(!(res.empty() && num == 0)) res.push_back(num + '0');
    }
    return res.empty() ? "0" : res;
}

int main() {
    string num1 = "123";
    string num2 = "456";
    cout << multiply(num1, num2) << "\n";
    return 0;
}