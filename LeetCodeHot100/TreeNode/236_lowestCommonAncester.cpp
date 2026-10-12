/*
236. 二叉树的最近公共祖先

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
*/
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* lowestCommonAncester(TreeNode* root, TreeNode* p, TreeNode* q){
    if(root == nullptr || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncester(root->left, p, q);
    TreeNode* right = lowestCommonAncester(root->right, p, q);
    if(left && right) return root;
    return left ? left : right;
}

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

int main(){
    vector<string> nodes = {"3", "5", "1", "6", "2", "0", "8", "null", "null", "7", "4"};
    TreeNode* root = buildTreeNode(nodes);
    TreeNode* p = root->left->right;
    TreeNode* q = root->right;
    cout << lowestCommonAncester(root, p, q)->val << "\n";
    return 0;
}