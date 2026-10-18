/*
1023. 驼峰式匹配

给你一个字符串数组 queries，和一个表示模式的字符串 pattern，请你返回一个布尔数组 answer 。只有在待查项 queries[i] 与模式串 pattern 匹配时， answer[i] 才为 true，否则为 false。

如果可以将 小写字母 插入模式串 pattern 得到待查询项 queries[i]，那么待查询项与给定模式串匹配。您可以在模式串中的任何位置插入字符，也可以选择不插入任何字符。
*/
#include <bits/stdc++.h>
using namespace std;

bool check(string query, string pattern){
    int n = pattern.size();
    int j = 0;
    for(char c : query){
        if(j < n && pattern[j] == c) j++;
        else if(isupper(c)) return false;
    }
    return j == n;
}

vector<bool> camelMatch(vector<string>& queries, string pattern){
    vector<bool> ans;
    ans.reserve(queries.size());
    for(const auto& query : queries){
        ans.push_back(check(query, pattern));
    }
    return ans;
}

int main(){
    vector<string> queries = {"FootBall", "FootBallBall", "FootBrall"};
    string pattern = "FBa";
    vector<bool> ans = camelMatch(queries, pattern);
    cout << boolalpha;
    for(auto it : ans) cout << it << " ";
    cout << "\n";
    return 0;
}