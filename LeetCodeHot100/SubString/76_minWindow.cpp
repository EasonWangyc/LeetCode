/*
76. 最小覆盖子串

给定两个字符串 s 和 t，长度分别是 m 和 n，返回 s 中的 最短窗口 子串，使得该子串包含 t 中的每一个字符（包括重复字符）。如果没有这样的子串，返回空字符串 ""。

测试用例保证答案唯一。
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

string minWindow(string s, string t){
    int m = s.length();
    unordered_map<char, int> need, window;
    for(char c : t) need[c]++;
    int n = need.size();
    int l = 0, r = 0;
    int start = 0, len = INT_MAX;
    int valid = 0;
    while(r < m){
        char c = s[r];
        r++;
        if(need.count(c)){
            window[c]++;
            if(need[c] == window[c]) valid++;
        }
        while(valid == n){
            if(r - l < len){
                start = l;
                len = r - l;
            }
            char d = s[l];
            l++;
            if(need.count(d)){
                if(need[d] == window[d]) valid--;
                window[d]--;
            }
        }
    }
    return len == INT_MAX ? "" : s.substr(start, len);
}

int main(){
    string s = "ADOBECODEBANC", t = "ABC";
    cout << minWindow(s, t) << "\n";
    return 0;
}