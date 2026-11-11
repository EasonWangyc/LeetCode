/*
30. 串联所有单词的子串

给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。

 s 中的 串联子串 是指一个包含  words 中所有字符串以任意顺序排列连接起来的子串。

例如，如果 words = ["ab","cd","ef"]， 那么 "abcdef"， "abefcd"，"cdabef"， "cdefab"，"efabcd"， 和 "efcdab" 都是串联子串。 "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。
返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> findSubString(string s, vector<string>& words) {
    int m = words[0].size();
    int window_len = m * words.size();
    int n = s.length();
    unordered_map<string, int> target_cnt;
    for(string word : words) target_cnt[word]++;
    vector<int> ans;
    if(n < window_len) return ans;
    for(int start = 0; start < m; start++) {
        unordered_map<string, int> cnt;
        // 统计过多的单词种数（包括不在words中的单词）
        int overload = 0;
        // 枚举右节点
        for(int right = start + m; right <= n; right += m) {
            string in_word = s.substr(right - m, m);
            if(cnt[in_word] == target_cnt[in_word]) overload++;
            cnt[in_word]++;
            int left = right - window_len;
            if(left < 0) continue;
            // overload==0等价于比较cnt==target_cnt但是更快
            if(overload == 0) ans.push_back(left);
            string out_word = s.substr(left, m);
            cnt[out_word]--;
            if(cnt[out_word] == target_cnt[out_word]) overload--;
        }
    }
    return ans;
}

int main() {
    string s = "barfoothefoobarman";
    vector<string> words = {"foo", "bar"};
    vector<int> ans = findSubString(s, words);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}