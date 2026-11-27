/*
106. 从中序与后序遍历序列构造二叉树

给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。
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
    for(int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << "\n";
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int n = postorder.size();
    if(n == 0) return nullptr;
    int left_size = ranges::find(inorder, postorder.back()) - inorder.begin();
    vector<int> in1(inorder.begin(), inorder.begin() + left_size);
    vector<int> in2(inorder.begin() + left_size + 1, inorder.end());
    vector<int> post1(postorder.begin(), postorder.begin() + left_size);
    // 注意不需要+1
    vector<int> post2(postorder.begin() + left_size, postorder.end() - 1);
    TreeNode* left = buildTree(in1, post1);
    TreeNode* right = buildTree(in2, post2);
    return new TreeNode(postorder.back(), left, right);
}

int main() {
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    TreeNode* root = buildTree(inorder, postorder);
    printLevelOrder(root);
    return 0;
}