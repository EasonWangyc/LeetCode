/*
95. 不同的二叉搜索树Ⅱ

给你一个整数 n ，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同 二叉搜索树 。可以按 任意顺序 返回答案。
*/
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

vector<TreeNode*> dfs(int start, int end) {
    vector<TreeNode*> ans;
    if(start > end) {
        ans.push_back(nullptr);
        return ans;
    }
    if(start == end) {
        TreeNode* cur = new TreeNode(start);
        ans.push_back(cur);
        return ans;
    }
    for(int i = start; i <= end; i++) {
        vector<TreeNode*> leftTrees = dfs(start, i - 1);
        vector<TreeNode*> rightTrees = dfs(i + 1, end);
        for(TreeNode* leftTree : leftTrees) {
            for(TreeNode* rightTree : rightTrees) {
                TreeNode* root = new TreeNode(i);
                root->left = leftTree;
                root->right = rightTree;
                ans.push_back(root);
            }
        }
    }
    return ans;
}

vector<TreeNode*> generateTrees(int n) {
    if(n == 0) return {nullptr};
    vector<TreeNode*> ans = dfs(1, n);
    return ans;
}

void printLevelOrder(TreeNode* root) {
    if(!root){
        cout << "null" << endl;
        return;
    }
    queue<TreeNode*> q;
    vector<string> result;
    q.push(root);
    while(!q.empty()){
        TreeNode* node = q.front();
        q.pop();
        if(node == nullptr){
            result.push_back("null");
            continue;
        }
        result.push_back(to_string(node->val));
        q.push(node->left);
        q.push(node->right);
    }
    while(!result.empty() && result.back() == "null") result.pop_back();
    for(int i = 0; i < result.size(); i++) cout << result[i] << " ";
    cout << "\n";
}

int main() {
    vector<TreeNode*> ans = generateTrees(3);
    for(TreeNode* tree : ans) printLevelOrder(tree);
    return 0;
}