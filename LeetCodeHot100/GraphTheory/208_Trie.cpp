/*
208. 实现 Trie (前缀树)

Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

请你实现 Trie 类：
Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

思路：参考二叉树，实现一个26叉树。
*/
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

struct Node
{
    Node* son[26]{};    // 26个槽位对应a~z，初始化均为空，对应nullptr，节点本身不存储具体字符，用0~25表示a~z
    bool end = false;   // 单词终止标志位，区分前缀和完整字符
};

class Trie{
private:
    Node* root = new Node();
    int find(string word){
        Node* cur = root;
        for(char c : word){
            int idx = c - 'a';
            if(cur->son[idx] == nullptr) return 0;    // 说明找不到，返回0
            cur = cur->son[idx];                      // 类似链表中的cur->next
        }
        return cur->end ? 2 : 1;                    // 尾标志为true，说明找到完整词，返回2，否则说明只是前缀，返回1
    }
    void destroy(Node* node){
        if(node == nullptr) return;
        for(Node* son : node->son) destroy(son);    // 递归删除所有孩子节点
        delete node;                                // 删除自身
    }
public:
    ~Trie(){
        destroy(root);                              // 对象析构时自动清理堆内存
    }
    void insert(string word){
        Node* cur = root;
        for(char c : word){
            int idx = c - 'a';
            if(cur->son[idx] == nullptr){
                cur->son[idx] = new Node();
            }
            cur = cur->son[idx];
        }
        cur->end = true;                            // 插入完整字符后把标志位置为true表示完整单词
    }
    bool search(string word){
        return find(word) == 2;
    }
    bool startsWith(string prefix){
        return find(prefix) != 0;                   // 三态中返回非0即可
    }
};

int main(){
    Trie* trie = new Trie();
    cout << boolalpha;
    trie->insert("apple");
    cout << trie->search("apple") << "\n";
    cout << trie->search("app") << "\n";
    cout << trie->startsWith("app") << "\n";
    trie->insert("app");
    cout << trie->search("app") << "\n";
    return 0;
}