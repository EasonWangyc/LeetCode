/*
112. 路径总和

给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

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

bool hasPathSum(TreeNode* root, int target) {
    if(!root) return false;
    // 走到叶子节点
    if(!root->left && !root->right) return root->val == target;
    int remain = target - root->val;
    return hasPathSum(root->left, remain) || hasPathSum(root->right, remain);
}

int main() {
    vector<string> nodes = {"5", "4", "8", "11", "null", "13", "4", "7", "2", "null", "null", "null", "null", "1"};
    TreeNode* root = buildTreeNode(nodes);
    cout << boolalpha << hasPathSum(root, 21) << "\n";
    return 0;
}