/*
1456. 定长子串中元音的最大数目

给你字符串 s 和整数 k 。

请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。
*/
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int maxVowels(string s, int k){
    unordered_set<char> mp = {'a', 'e', 'i', 'o', 'u'};
    int ans = 0, cur = 0;
    for(int i = 0; i < s.length(); i++){
        if(mp.count(s[i])) cur++;
        int l = i - k + 1;
        if(l < 0) continue;
        ans = max(ans, cur);
        if(mp.count(s[l])) cur--;
    }
    return ans;
}

int main(){
    string s = "aeiou";
    int k = 3;
    cout << maxVowels(s, k) << "\n";
    return 0;
}