/*
60. 排列序列

给出集合 [1,2,3,...,n]，其所有元素共有 n! 种排列。

按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：

"123"
"132"
"213"
"231"
"312"
"321"
给定 n 和 k，返回第 k 个排列。
*/
#include <bits/stdc++.h>
using namespace std;

// 以k=373，数组为1~6为例，以1开头的全排列有5!种，2~6同理，所以k=373时，对应排列的第一个数字应该是k/5!

string getPermutation(int n, int k) {
    // 计算阶乘，factorial[i]=i!
    vector<int> factorial(n + 1);
    factorial[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
    // 初始化1~n数组，对应索引0~n-1
    vector<int> nums(n);
    string ans;
    // 例如k=120，数组为1~6，以 1 开头的是第120个，对应下标索引0，必须先k--
    k--;
    for(int i = 0; i < n; i++) nums[i] = i + 1;
    for(int i = n - 1; i >= 0; i--) {
        // 第一次k对(n-1)!取模
        int idx = k / factorial[i];
        ans.push_back(nums[idx] + '0');
        // 数组删除order，同时保持其他顺序不变
        nums.erase(nums.begin() + idx);
        k %= factorial[i];
    }
    return ans;
}

int main() {
    cout << getPermutation(4, 9) << "\n";
    return 0;
}