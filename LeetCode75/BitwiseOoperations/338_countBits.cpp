/*
338. 比特位计数

给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数 ，返回一个长度为 n + 1 的数组 ans 作为答案。

不要使用内置函数来解决（例如，C++ 中的 __builtin_popcount）。

考虑奇偶
对于一个奇数i，它的1比i-1多1；
对于一个偶数i，它的1和i/2一样多，因为相当于左移一位
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> countBits(int n) {
    vector<int> ans(n + 1);
    ans[0] = 0;
    for(int i = 1; i <= n; i++){
        if(i  % 2 == 1) ans[i] = ans[i - 1] + 1;
        else ans[i] = ans[i / 2];
    }
    return ans;
}

int main() {
    vector<int> ans = countBits(10);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}