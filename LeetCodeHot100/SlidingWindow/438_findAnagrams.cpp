/*
给定两个字符串 s 和 p，找到 s 中所有 p 的字母异位词的起始索引。字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20,100。

示例：
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。

思路：先用一个数组记录p中每个字符出现的次数，然后使用一个滑动窗口在s中遍历，每次移动右指针r时更新窗口中字符的出现次数，左指针为l，如果当前窗口中的字符出现次数与p中字符出现次数相同，则说明找到了一个字母异位词，记录下起始索引l。
*/
#include <vector>
#include <iostream>
using namespace std;

vector<int> findAnagrams(string s,string p){
    int n = p.length(), m = s.length();
    vector<int> ans;
    vector<char> array1(26, 0);
    for(char c : p) array1[c- 'a']++;
    vector<char> array2(26, 0);
    for(int l = 0; l < m - n + 1; l++){
        array2[s[l] - 'a']++;
        int r = l + n - 1;
        if(array1 == array2) ans.push_back(l);
        array2[s[l] - 'a']--;
    }
    return ans;
}

int main(){
    string s = "cbaebabacd", p = "abc";
    vector<int> ans = findAnagrams(s, p);
    for(int i : ans) cout << i << " ";
    cout << endl;
    return 0;
}