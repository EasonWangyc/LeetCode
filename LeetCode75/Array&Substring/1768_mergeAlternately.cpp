/*
1768. 交替合并字符串

给你两个字符串 word1 和 word2 。请你从 word1 开始，通过交替添加字母来合并字符串。如果一个字符串比另一个字符串长，就将多出来的字母追加到合并后字符串的末尾。
返回 合并后的字符串 。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string mergeAlternately(string word1, string word2){
    string ans = "";
    int n = word1.length(), m = word2.length();
    for(int i = 0; i < n || i < m; i++){
        if(i < n) ans.push_back(word1[i]);
        if(i < m) ans.push_back(word2[i]);
    }
    return ans;
}

int main(){
    string word1 = "ab", word2 = "pcqr";
    cout << mergeAlternately(word1, word2) << "\n";
    return 0;
}