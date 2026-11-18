/*
87. 扰乱字符串

使用下面描述的算法可以扰乱字符串 s 得到字符串 t ：
如果字符串的长度为 1 ，算法停止
如果字符串的长度 > 1 ，执行下述步骤：
在一个随机下标处将字符串分割成两个非空的子字符串。即，如果已知字符串 s ，则可以将其分成两个子字符串 x 和 y ，且满足 s = x + y 。
随机 决定是要「交换两个子字符串」还是要「保持这两个子字符串的顺序不变」。即，在执行这一步骤之后，s 可能是 s = x + y 或者 s = y + x 。
在 x 和 y 这两个子字符串上继续从步骤 1 开始递归执行此算法。
给你两个 长度相等 的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。如果是，返回 true ；否则，返回 false 。
*/
#include <bits/stdc++.h>
using namespace std;

bool isScramble(string s1, string s2) {
    if(s1 == s2) return true;
    
    string t1 = s1, t2 = s2;
    sort(t1.begin(), t1.end());
    sort(t2.begin(), t2.end());
    if(t1 != t2) return false;

    int n = s1.length();
    unordered_map<string, bool> memo;
    string key = s1 + '_' + s2;
    if(memo.count(key)) return memo[key];
    for(int i = 1; i < n; i++) {
        if(isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) return memo[key] = true;
        if(isScramble(s1.substr(0, i), s2.substr(n - i)) && 
        isScramble(s1.substr(i), s2.substr(0, n - i))) return memo[key] = true;
    }
    return memo[key] = false;
}

int main() {
    string s1 = "great";
    string s2 = "rgeat";
    cout << boolalpha << isScramble(s1, s2) << "\n";
    return 0;
}