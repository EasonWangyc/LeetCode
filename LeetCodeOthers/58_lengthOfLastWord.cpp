/*
58. 最后一个单词的长度

给你一个字符串 s，由若干单词组成，单词前后用一些空格字符隔开。返回字符串中 最后一个 单词的长度。
单词 是指仅由字母组成、不包含任何空格字符的最大子字符串。
*/
#include <bits/stdc++.h>
using namespace std;

int lengthOfLastWord(string s){
    int n = s.length();
    int i = n - 1;
    while(s[i] == ' ' && i >= 0) i--;
    int j = i - 1;
    while(s[j] != ' ' && j >= 0) j--;
    return i - j;
}

int main(){
    string s = "Hello World  ";
    cout << lengthOfLastWord(s) << "\n";
    return 0;
}