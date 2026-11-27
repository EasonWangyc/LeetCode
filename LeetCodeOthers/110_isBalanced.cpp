/*
110. 平衡二叉树

给定一个二叉树，判断它是否是平衡二叉树。
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

int checkHeight(TreeNode* root) {
    if(!root) return 0;
    int leftH = checkHeight(root->left);
    if(leftH == -1) return -1;
    int rightH = checkHeight(root->right);
    if(rightH == -1) return -1;
    if(abs(leftH - rightH) > 1) return -1;
    return max(leftH, rightH) + 1;
}

bool isBalanced(TreeNode* root) {
    return checkHeight(root) != -1;
}

int main() {
    vector<string> nodes = {"3", "9", "20", "null", "null", "15", "7"};
    TreeNode* root = buildTreeNode(nodes);
    cout << boolalpha << isBalanced(root) << "\n";
    return 0;
}