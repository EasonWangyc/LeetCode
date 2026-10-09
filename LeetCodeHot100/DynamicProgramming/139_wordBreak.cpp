/*
139. 单词拆分

给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
*/
#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

bool wordBreak(string s, vector<string>& wordDict){
    unordered_set<string> wordset(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j < i; j++){
            if(dp[j] && wordset.count(s.substr(j, i - j))){
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

int main(){
    vector<string> wordDict = {"leet", "code"};
    string s = "leetcode";
    cout << boolalpha << wordBreak(s, wordDict) << "\n";
    return 0;
}