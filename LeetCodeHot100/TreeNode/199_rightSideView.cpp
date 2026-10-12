/*
199. 二叉树的右视图

给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
*/
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeNode(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") {
        return nullptr;
    }

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    int index = 1;

    while (!nodeQueue.empty() && index < static_cast<int>(nodes.size())) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();

        if (index < static_cast<int>(nodes.size()) && nodes[index] != "null") {
            current->left = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(current->left);
        }
        ++index;

        if (index < static_cast<int>(nodes.size()) && nodes[index] != "null") {
            current->right = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(current->right);
        }
        ++index;
    }
    return root;
}

void dfs(TreeNode* node, int depth, vector<int>& ans){
    if(node == nullptr) return;
    if(depth == ans.size()) ans.push_back(node->val);
    dfs(node->right, depth + 1, ans);
    dfs(node->left, depth + 1, ans);
}

int main(){
    vector<string> nodes = {"1", "2", "3", "null", "5", "null", "4"};
    TreeNode* root = buildTreeNode(nodes);
    vector<int> ans;
    dfs(root, 0, ans);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}