/*
763. 划分字母区间

给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。例如，字符串 "ababcc" 能够被分为 ["abab", "cc"]，但类似 ["aba", "bcc"] 或 ["ab", "ab", "cc"] 的划分是非法的。
注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。
返回一个表示每个字符串片段的长度的列表。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> partitionLabels(string s){
    vector<int> last(26, 0);
    int n = s.length();
    for(int i = 0; i < n; i++) last[s[i] - 'a'] = i;
    vector<int> ans;
    int start = 0, far = 0;
    for(int i = 0; i < n; i++){
        far = max(far, last[s[i] - 'a']);
        // 当遍历指针 i 终于追上了当前片段内所有字符的最远右边界
        if(i == far){
            ans.push_back(i - start + 1);
            start = i + 1;
        }
    }
    return ans;
}

int main(){
    string s = "sdnlsjdlajporuhrbb";
    vector<int> ans = partitionLabels(s);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}