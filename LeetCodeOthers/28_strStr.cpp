/*
28. 找出字符串中第一个匹配项的下标

给你两个字符串haystack和needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。
*/
#include <bits/stdc++.h>
using namespace std;

int strStr(string haystack, string needle) {
    int m = haystack.length(), n = needle.length();
    if(m < n) return -1;
    for(int i = 0; i <= m - n; i++) {
        int j = 0;
        while(j < n && haystack[i + j] == needle[j]) j++;
        if(j == n) return i;
    }
    return -1;
}

int main() {
    string haystack = "sadlsjdlhldb", needle = "sad";
    cout << strStr(haystack, needle) << "\n";
    return 0;
}