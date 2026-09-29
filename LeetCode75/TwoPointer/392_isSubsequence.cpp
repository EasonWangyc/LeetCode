/*
392. 判断子序列

给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。
*/
#include <iostream>
#include <vector>
using namespace std;

bool isSubsequence(string s, string t){
    int n = s.length(), m = t.length();
    if(n == 0) return true;
    for(int i = 0, j = 0; j < m; j++){
        if(s[i] == t[j]) i++;
        if(i == n) return true; // 注意是n
    }
    return false;
}

int main(){
    string s = "axc", t = "asdnlgbsdc";
    cout << boolalpha << isSubsequence(s, t) << "\n";
    return 0;
}