/*
89. 格雷编码

n 位格雷码序列 是一个由 2^n 个整数组成的序列，其中：
每个整数都在范围 [0,2^n - 1] 内（含 0 和 2^n - 1）
第一个整数是 0
一个整数在序列中出现 不超过一次
每对 相邻 整数的二进制表示 恰好一位不同 ，且第一个 和 最后一个 整数的二进制表示 恰好一位不同

给你一个整数 n ，返回任一有效的 n 位格雷码序列 。

思路：对于n+1位格雷码，在n位格雷码的基础上，先对原数组元素开头加一个0（相当于不变），然后将其倒序并每位开头加1，接入原数组即可
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> grayCode(int n) {
    vector<int> res;
    res.push_back(0);
    // 用于表示前面加上的1
    int head = 1;
    for(int i = 0; i < n; i++) {
        for(int j = (int)res.size() - 1; j >= 0; j--) res.push_back(head + res[j]);
        head <<= 1;
    }
    return res;
}

int main() {
    vector<int> ans = grayCode(3);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}