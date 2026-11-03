/*
1268. 搜索推荐系统

给你一个产品数组 products 和一个字符串 searchWord ，products  数组中每个产品都是一个字符串。

请你设计一个推荐系统，在依次输入单词 searchWord 的每一个字母后，推荐 products 数组中前缀与 searchWord 相同的最多三个产品。如果前缀相同的可推荐产品超过三个，请按字典序返回最小的三个。

请你以二维列表的形式，返回在输入 searchWord 每个字母后相应的推荐产品的列表。
*/
#include <bits/stdc++.h>
using namespace std;

class solution {
private:
    struct TrieNode {
        TrieNode* children[26]{};
        vector<string> suggestions;
    };

    TrieNode* root;

    void insert(const string& word) {
        TrieNode* cur = root;
        for(char c : word) {
            int idx = c - 'a';
            if(cur->children[idx] == nullptr) cur->children[idx] = new TrieNode();
            cur = cur->children[idx];
            if(cur->suggestions.size() < 3) cur->suggestions.push_back(word);
        }
    }
public:
    vector<vector<string>> suggestedProduct(vector<string>& products, string searchWord) {
        root = new TrieNode();
        sort(products.begin(), products.end());
        for(const string& word : products) insert(word);
        vector<vector<string>> ans;
        TrieNode* cur = root;
        bool mismatch = false;
        for(char c : searchWord) {
            int idx = c - 'a';
            if(mismatch || !cur->children[idx]) {
                mismatch = true;
                ans.push_back({});
            }else {
                cur = cur->children[idx];
                ans.push_back(cur->suggestions);
            }
        }
        return ans;
    }
};

int main() {
    vector<string> products = {"bags", "baggage", "banner", "box", "cloths"};
    string searchWord = "bags";
    solution s;
    vector<vector<string>> ans = s.suggestedProduct(products, searchWord);
    for(auto& ss : ans) {
        for(string s : ss) cout << s << " ";
        cout << "\n";
    } 
    return 0;
}