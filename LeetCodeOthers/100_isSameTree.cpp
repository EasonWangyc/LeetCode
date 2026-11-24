/*
100. 相同的树

给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
*/
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
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
    // 由于队列先进先出的特性下一层循环会先处理同一层的left再处理right
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

bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr && q == nullptr) return true;
    if(p && q && p->val == q->val) return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    return false;
}

int main() {
    vector<string> a = {"1", "2", "3"};
    vector<string> b = {"1", "2", "3"};
    TreeNode* p = buildTreeNode(a);
    TreeNode* q = buildTreeNode(b);
    cout << boolalpha << isSameTree(p, q) << "\n";
    return 0;
}