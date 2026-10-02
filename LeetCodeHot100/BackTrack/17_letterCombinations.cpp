/*
17. 电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
*/
#include <iostream>
#include <vector>
using namespace std;

const vector<string> map = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; // 2~9

void backtrack(string& digits, int index, string& path, vector<string>& ans){
    if(path.length() == digits.length()){
        ans.push_back(path);
        return;
    }
    int digit = digits[index] - '2';
    string letter = map[digit];
    for(auto& c : letter){
        path.push_back(c);
        backtrack(digits, index + 1, path, ans);
        path.pop_back();
    }
}

vector<string> letterCombinations(string digits){
    if(digits.empty()) return {};
    vector<string> ans;
    string path;
    backtrack(digits, 0, path, ans);
    return ans;
}

int main(){
    string digits = "24";
    vector<string> ans = letterCombinations(digits);
    for(auto& s : ans) cout << s << " ";
    cout << "\n";
    return 0;
}