/*
5. 最长回文子串

给你一个字符串 s，找到 s 中最长的 回文 子串。
*/
#include <vector>
#include <iostream>
using namespace std;

string longestPalindrome(string s){
    int n = s.length();
    int left = 0, right = 0;
    for(int i = 0; i < 2 * n - 1; i++){
        // 当i为偶数时，l=r，对应奇数长度回文串，当i为奇数时，l=r-1，对应偶数长度回文串
        int l = i / 2, r = (i + 1) / 2;
        while(l > 0 && r < n && s[l] == s[r]){
            l--;
            r++;
        }
        // while结束后l在回文串左边一位，r在回文串右边一位，r-1-(l+1)+1=r-l-1
        if(r - l - 1 > right - left){
            left = l + 1;
            right = r;
            // 核心更新逻辑
        }
    }
    return s.substr(left, right - left); // substr左闭右开区间，第二个参数为长度，正好是r - l - 1
}

int main(){
    string s = "babad";
    cout << longestPalindrome(s) << "\n";
    return 0; 
}