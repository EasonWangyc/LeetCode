/*
14. 最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。
*/
#include <bits/stdc++.h>
using namespace std;

string find(string& a, string& b) {
    string ans = "";
    int m = a.length(), n = b.length();
    for(int i = 0; i < m && i < n; i++) {
        if(a[i] == b[i]) ans += a[i];
        else break;
    }
    return ans;
}

string longestCommonPrefix(vector<string>& strs) {
    string ans = strs[0];
    int n = strs.size();
    for(int i = 1; i < n; i++) {
        ans = find(ans, strs[i]);
    }
    return ans;
}

int main() {
    vector<string> strs = {"flower", "flow", "flight"};
    cout << longestCommonPrefix(strs) << "\n";
    return 0;
}