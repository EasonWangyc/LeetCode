/*
3. 无重复字符的最长子串

给定一个字符串 s ，请你找出其中不含有重复字符的最长子串的长度。
*/
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

int lengthOfLongestSubstring(string s) {
    int ans = 0;
    int l = 0;
    int n = s.length();
    unordered_map<char, int> mp;
    for(int r = 0; r < n; r++){
        mp[s[r]]++;
        while(mp[s[r]] > 1){
            mp[s[l]]--;
            l++;
        }
        ans = max(ans, r - l + 1);
    }
    return ans;
}

int main(){
    string s = "bbsadglgjalbb";
    cout << lengthOfLongestSubstring(s) << endl;
    return 0;
}