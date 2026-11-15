/*
66. 加一

给定一个表示 大整数 的整数数组 digits，其中 digits[i] 是整数的第 i 位数字。这些数字按从左到右，从最高位到最低位排列。这个大整数不包含任何前导 0。

将大整数加 1，并返回结果的数字数组。
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();
    int plus = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(i == n - 1) plus = digits[i] + 1;
        else plus += digits[i];
        if(plus <= 9) {
            digits[i] = plus;
            plus = 0;
            break;
        }
        else {
            plus = 1;
            digits[i] = 0;
        }
    }
    if(plus) digits.insert(digits.begin(), 1);
    return digits;
}

// 极致优化：只要当前位不是9，直接return即可
/*
vector<int> plusOne(vector<int>& digits) {
    for (int i = (int)digits.size() - 1; i >= 0; i--) {
        if (digits[i] != 9) {
            digits[i]++;
            return digits; // 不产生进位，直接结束返回
        }
        digits[i] = 0; // 当前位是 9，加 1 变 0，自动进入下一轮给高位加 1
    }

    // 能走到这里，说明原数组全是 9（如 999），此时 digits 已经全变成 000
    digits.push_back(0); // 末尾补一个 0，长度变为 n + 1
    digits[0] = 1;       // 最高位设为 1，变成 1000，零元素平移开销
    return digits;
}
*/

int main() {
    vector<int> digits = {9, 8};
    plusOne(digits);
    for(int digit : digits) cout << digit << " ";
    cout << "\n";
    return 0;
}