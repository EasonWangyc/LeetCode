/*
151. 反转字符串中的单词

给你一个字符串 s ，请你反转字符串中 单词 的顺序。

单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。

返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。

注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

示例
输入：s = "the sky is blue  "
输出："blue is sky the"

思路：倒序+双指针提取单词
*/
#include <vector>
#include <iostream>
using namespace std;

string reserveWords(string s){
    int n = s.length();
    int i = n - 1;
    vector<string> words;
    while(s[i] == ' ') i--;
    int j = i;
    while(i >= 0){
        while(i >= 0 && s[i] != ' ') i--;
        if(i != j) words.push_back(s.substr(i + 1, (j - i)));
        while(i >= 0 && s[i] == ' '){
            i--;
            j = i;
        }
    }
    string ans = "";
    for(int i = 0; i < words.size(); i++){
        ans += words[i];
        if(i != words.size() - 1) ans += ' ';
    }
    return ans;
}

int main(){
    string s = "the sky is blue  ";
    cout << reserveWords(s) << "\n";
    return 0;
}