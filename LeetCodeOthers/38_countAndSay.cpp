/*
38. 外观数列

「外观数列」是一个数位字符串序列，由递归公式定义：

countAndSay(1) = "1"
countAndSay(n) 是 countAndSay(n-1) 的行程长度编码。
 

行程长度编码（RLE）是一种字符串压缩方法，其工作原理是通过将每个最大连续相同字符组替换为该组的长度后加上该字符本身。例如，要压缩字符串 "3322251" ，我们将 "33" 用 "23" 替换，将 "222" 用 "32" 替换，将 "5" 用 "15" 替换并将 "1" 用 "11" 替换。因此压缩后字符串变为 "23321511"。

给定一个整数 n ，返回 外观数列 的第 n 个元素。
*/
#include <bits/stdc++.h>
using namespace std;

string countAndSay(int n) {
    string cur = "1";
    for(int i = 2; i <= n; i++) {
        string next = "";
        int len = cur.length();
        int j = 0;
        while(j < len) {
            int k = j;
            while(k < len && cur[k] == cur[j]) k++;
            next += to_string(k - j);
            next += cur[j];
            j = k;
        }
        cur = move(next);
    }
    return cur;
}

int main() {
    cout << countAndSay(5) << "\n";
    return 0;
}