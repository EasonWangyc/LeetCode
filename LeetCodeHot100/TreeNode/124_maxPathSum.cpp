/*
124. 二叉树中的最大路径和

二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。
*/
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int dfs(TreeNode* node, int& ans){
    if(node == nullptr) return 0;
    int l_val = dfs(node->left, ans);
    int r_val = dfs(node->right, ans);
    ans = max(ans, l_val + r_val + node->val);
    return max(max(l_val, r_val) + node->val, 0);
}

int maxPathSum(TreeNode* root){
    int ans = INT_MIN;
    dfs(root, ans);
    return ans;
}

TreeNode* buildTreeNode(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);

    int idx = 1;
    while (!q.empty() && idx < nodes.size()) {
        TreeNode* cur = q.front();
        q.pop();

        // 构造左子节点
        if (idx < nodes.size() && nodes[idx] != "null") {
            cur->left = new TreeNode(stoi(nodes[idx]));
            q.push(cur->left);
        }
        idx++;

        // 构造右子节点
        if (idx < nodes.size() && nodes[idx] != "null") {
            cur->right = new TreeNode(stoi(nodes[idx]));
            q.push(cur->right);
        }
        idx++;
    }
    return root;
}

int main() {
    vector<string> tree1 = {"-10", "9", "20", "null", "null", "15", "7"};
    TreeNode* root1 = buildTreeNode(tree1);
    cout << maxPathSum(root1) << endl; // 输出: 42
    vector<string> tree2 = {"-3"};
    TreeNode* root2 = buildTreeNode(tree2);
    cout << maxPathSum(root2) << endl; // 输出: -3
    return 0;
}