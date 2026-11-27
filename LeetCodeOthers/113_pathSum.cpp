/*
113. 路径总和Ⅱ

给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。

叶子节点 是指没有子节点的节点。
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
    while(!nodeQueue.empty() && index < (int)nodes.size()){
        TreeNode* cur = nodeQueue.front();
        nodeQueue.pop();
        if(index < (int)nodes.size() && nodes[index] != "null"){
            cur->left = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(cur->left);
        }
        index++;
        if(index < (int)nodes.size() && nodes[index] != "null"){
            cur->right = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(cur->right);
        }
        index++;
    }
    return root;
}

void backtrack(TreeNode* node, int remain, vector<vector<int>>& ans, vector<int>& path) {
    if(node == nullptr) return;
    path.push_back(node->val);
    remain -= node->val;
    if(!node->left && !node->right && remain == 0) ans.push_back(path);
    backtrack(node->left, remain, ans, path);
    backtrack(node->right, remain, ans, path);
    // 如果按引用传递remain需要手动remain+=node->val
    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> ans;
    vector<int> path;
    backtrack(root, targetSum, ans, path);
    return ans;
}

int main() {
    vector<string> nodes = {"5", "4", "8", "11", "null", "13", "4", "7", "2", "null", "null", "5", "1"};
    TreeNode* root = buildTreeNode(nodes);
    vector<vector<int>> ans = pathSum(root, 22);
    for(auto& it : ans) {
        for(int num : it) cout << num << " ";
        cout << "\n";
    }
    return 0;
}