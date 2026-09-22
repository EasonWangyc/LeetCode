/*
给你一棵二叉树的根节点 root ，请你将它展开为一个单链表：展开后的单链表应该使用原二叉树的节点，按照 先序遍历 顺序排列。

示例：
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]

思路：递归。定义一个head节点，先递归地展开右子树，再递归地展开左子树，然后将当前节点的左子树置空，右子树指向head，最后更新head为当前节点。
*/
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* head = nullptr;

void flatten(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    flatten(root->right);
    flatten(root->left);
    root->left = nullptr;
    root->right = head;
    head = root;
}

int main() {
    // 手动构建 root = [1,2,5,3,4,null,6]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);
    flatten(root);
    TreeNode* cur = root;
    while(cur){
        cout << cur->val << " ";
        cur = cur->right;
    }
    return 0;
}