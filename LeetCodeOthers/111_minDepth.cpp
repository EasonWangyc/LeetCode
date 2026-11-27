/*
111. 二叉树的最小深度

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明：叶子节点是指没有子节点的节点。
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

int minDepth(TreeNode* root) {
    if(!root) return 0;
    if(!root->left && !root->right) return 1;
    int l = minDepth(root->left), r = minDepth(root->right);
    // 关键是这一行，对应用例2
    if(!root->left || !root->right) return l + r + 1;
    return min(l, r) + 1;
}

int main() {
    vector<string> nodes1 = {"3", "9", "20", "null", "null", "15", "7"};
    TreeNode* root1 = buildTreeNode(nodes1);
    vector<string> nodes2 = {"2", "null", "3", "null", "4", "null", "5", "null", "6"};
    TreeNode* root2 = buildTreeNode(nodes2);
    cout << minDepth(root1) << " " << minDepth(root2) << "\n";
    return 0;
}