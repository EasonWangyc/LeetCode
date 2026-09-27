/*
345. 反转字符串中的元音字母

给你一个字符串 s ，仅反转字符串中的所有元音字母，并返回结果字符串。
元音字母包括 'a'、'e'、'i'、'o'、'u'，且可能以大小写两种形式出现不止一次。

思路：双指针双向查找元音字母
*/
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

void reserveVowels(string& s){
    int l = 0, r = s.length() - 1;
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    while(l < r){
        while(l < s.length() && !vowels.count(s[l])) l++;
        while(r > 0 && !vowels.count(s[r])) r--;
        if(l >= r) break;
        swap(s[l++], s[r--]);
    }
}

int main(){
    string s = "Leetcode";
    reserveVowels(s);
    cout << s << "\n";
    return 0;
}