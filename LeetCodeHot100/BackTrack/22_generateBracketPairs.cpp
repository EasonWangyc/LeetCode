/*
22. 括号生成

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
*/
#include <vector>
#include <iostream>
using namespace std;

void backtrack(int n, int left, int right, string& path, vector<string>& ans){
    if(path.length() == (long unsigned int)2 * n){
        ans.push_back(path);
        return;
    }
    // 都不能取等号
    if(left < n){
        path.push_back('(');
        backtrack(n, left + 1, right, path, ans);
        path.pop_back();
    }
    if(right < left){
        path.push_back(')');
        backtrack(n, left, right + 1, path, ans);
        path.pop_back();
    }
}

vector<string> generateBracketPairs(int n){
    vector<string> ans;
    string path;
    backtrack(n, 0, 0, path, ans);
    return ans;
}

int main(){
    vector<string> ans = generateBracketPairs(3);
    for(auto& s : ans) cout << s << " ";
    cout << "\n";
    return 0;
}