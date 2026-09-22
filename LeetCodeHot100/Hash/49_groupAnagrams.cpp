/*
49. 字母异位词分组

给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
*/
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<string>> groupAnagram(vector<string>& strs){
    unordered_map<string, vector<string>> mp;
    for(string s : strs){
        string sorted_s = s;
        sort(sorted_s.begin(), sorted_s.end());
        mp[sorted_s].push_back(s);
    }
    vector<vector<string>> ans;
    ans.reserve(mp.size());
    for(auto& it : mp){
        ans.push_back(it.second);
    }
    return ans;
}

int main(){
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> ans = groupAnagram(strs);
    for(auto& it : ans){
        for(string s : it){
            cout << s << " ";
        }
        cout << "\n";
    }
    return 0;
}