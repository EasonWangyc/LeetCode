/*
1047. 删除字符串中的所有相邻重复项

给出由小写字母组成的字符串 s，重复项删除操作 会选择两个相邻且相同的字母，并删除它们。

在 s 上反复执行重复项删除操作，直到无法继续删除。

在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
*/
#include <bits/stdc++.h>
using namespace std;

string removeDuplicates(string s){
    string ans = "";
    for(char c : s){
        if(!ans.empty() && c == ans.back()) ans.pop_back();
        else ans += c;
    }
    return ans;
}

int main(){
    string s = "aabbbbbcsl";
    cout << removeDuplicates(s) << "\n";
    return 0;
}