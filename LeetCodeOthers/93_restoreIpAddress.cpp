/*
93. 复原 IP 地址

有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。
*/
#include <bits/stdc++.h>
using namespace std;

// 左闭右开
bool is_valid(string s, int i, int j) {
    if(j - i > 3 || (j - i > 1 && s[i] == '0')) return false;
    return stoi(s.substr(i, j - i)) <= 255;
}

vector<string> restoreIpAddress(string s) {
    int n = s.length();
    vector<string> ans;
    for(int i = 1; i < n && is_valid(s, 0, i); i++) {
        for(int j = i + 1; j < n && is_valid(s, i, j); j++) {
            for(int k = j + 1; k < n && is_valid(s, j, k); k++) {
                if(is_valid(s, k, n)) ans.push_back(s.substr(0, i) + '.' + s.substr(i, j - i) + '.' + s.substr(j, k - j) + '.' + s.substr(k));
            }
        }
    }
    return ans;
}

int main() {
    string s = "25525511135";
    vector<string> strs =restoreIpAddress(s);
    for(string str : strs) cout << str << "\n";
    return 0;
}