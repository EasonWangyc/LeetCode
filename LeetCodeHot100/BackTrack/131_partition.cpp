/*
131. 分割回文串

给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。
*/
#include <vector>
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& s, int start, int end){
    while(start < end){
        if(s[start++] != s[end--]) return false;
    }
    return true;
}

void backtrack(const string& s, int startIndex, vector<vector<string>>& ans, vector<string> path){
    int n = s.length();
    if(startIndex == n){   // 说明遍历到最后了
        ans.push_back(path);
        return;
    }
    for(int i = startIndex; i < n; i++){
        // 先判断[startIndex, i]是否回文
        if(isPalindrome(s, startIndex, i)){
            string cur = s.substr(startIndex, i - startIndex + 1);
            path.push_back(cur);
            backtrack(s, i + 1, ans, path);
            path.pop_back();
        }
    }
}

vector<vector<string>> partition(string s){
    vector<vector<string>> ans;
    vector<string> path;
    backtrack(s, 0, ans, path);
    return ans;
}

int main(){
    string s = "aaabbcsdk";
    vector<vector<string>> ans = partition(s);
    for(auto& ss : ans){
        for(auto& s : ss){
            cout << s << " ";
        }
        cout << "\t";
    }
    cout << "\n";
    return 0;
}