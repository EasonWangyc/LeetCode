/*
107. 二叉树的层序遍历Ⅱ

给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
*/
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* buildTreeNode(const vector<string>& nodes){
    if(nodes.empty() || nodes[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    int index = 1;
    while(!nodeQueue.empty() && index < nodes.size()){
        TreeNode* cur = nodeQueue.front();
        nodeQueue.pop();
        if(index < nodes.size() && nodes[index] != "null"){
            cur->left = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(cur->left);
        }
        index++;
        if(index < nodes.size() && nodes[index] != "null"){
            cur->right = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(cur->right);
        }
        index++;
    }
    return root;
}

vector<vector<int>> levelOrderBottom(TreeNode* root) {
    if(!root) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        vector<int> ref;
        for(int i = q.size(); i--;) {
            TreeNode* node = q.front();
            q.pop();
            ref.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        ans.push_back(move(ref));
    }
    ranges::reverse(ans);
    return ans;
}

int main() {
    vector<string> nodes = {"3", "9", "20", "null", "null", "15", "7"};
    TreeNode* root = buildTreeNode(nodes);
    vector<vector<int>> ans = levelOrderBottom(root);
    for(auto& it : ans) {
        for(int num : it) cout << num << " ";
        cout << "\n";
    }
    return 0;
}