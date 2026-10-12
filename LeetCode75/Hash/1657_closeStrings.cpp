/*
1657. 确定两个字符串是否接近

如果可以使用以下操作从一个字符串得到另一个字符串，则认为两个字符串 接近 ：

操作 1：交换任意两个 现有 字符。
例如，abcde -> aecdb
操作 2：将一个 现有 字符的每次出现转换为另一个 现有 字符，并对另一个字符执行相同的操作。
例如，aacabb -> bbcbaa（所有 a 转化为 b ，而所有的 b 转换为 a ）
你可以根据需要对任意一个字符串多次使用这两种操作。

给你两个字符串，word1 和 word2 。如果 word1 和 word2 接近 ，就返回 true ；否则，返回 false 。

思路：操作1就是看a和b中的字符集合是否相同，操作2就是看a和b中字符出现次数的集合是否相同
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

bool closeStrings(string word1, string word2){
    if(word1.length() != word2.length()) return false;
    unordered_set<char> set1(word1.begin(), word1.end());
    unordered_set<char> set2(word2.begin(), word2.end());
    if (set1 != set2) return false;
    vector<int> cnt1(26), cnt2(26);
    for(int i = 0; i < word1.length(); i++){
        cnt1[word1[i] - 'a']++;
        cnt2[word2[i] - 'a']++;
    }
    sort(cnt1.begin(), cnt1.end());
    sort(cnt2.begin(), cnt2.end());
    if(cnt1 != cnt2) return false;
    return true;
}

int main(){
    string word1 = "cabbba", word2 = "abbccc";
    cout << boolalpha << closeStrings(word1, word2) << "\n";
    return 0;
}