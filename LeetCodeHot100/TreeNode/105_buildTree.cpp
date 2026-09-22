/*
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

思路：
先序遍历的第一个元素一定是根节点。
在中序遍历中找到这个根节点的位置，左边是左子树，右边是右子树，从而得到左子树的大小 left_size。
再根据 left_size 把先序遍历切成 [左子树][右子树]，递归构造左右子树。

二叉树的三种遍历方式（以A->B->C为例）
前序遍历（先根遍历，NLR）：规则是根节点 -> 左子树 -> 右子树。也就是先访问根节点，再递归访问左子树，最后访问右子树。（A->B->C）
中序遍历（中根遍历，LNR）：规则是左子树 -> 根节点 -> 右子树。也就是先递归访问左子树，再访问根节点，最后访问右子树。（B->A->C）
后序遍历（后根遍历，LRN）：规则是左子树 -> 右子树 -> 根节点。也就是先递归访问左子树，再访问右子树，最后访问根节点。（B->C->A）
*/
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// pre_l: 当前子树在先序遍历中的起点
// pre_r: 当前子树在先序遍历中的终点（开区间，不含）
// in_l:  当前子树在中序遍历中的起点
TreeNode* dfs(vector<int>& preorder, unordered_map<int, int>& index,
              int pre_l, int pre_r, int in_l) {
    if (pre_l == pre_r) {
        return nullptr;
    }

    int root_val = preorder[pre_l];
    int left_size = index[root_val] - in_l;   // 根节点在中序里的位置减去中序起点，即左子树大小

    TreeNode* left  = dfs(preorder, index, pre_l + 1, pre_l + 1 + left_size, in_l);
    TreeNode* right = dfs(preorder, index, pre_l + 1 + left_size, pre_r, in_l + left_size + 1);

    TreeNode* root = new TreeNode(root_val);
    root->left  = left;
    root->right = right;
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder){
    int n = preorder.size();
    // 值 -> 在中序遍历中的下标，O(1) 定位根
    unordered_map<int, int> index;              
    for(int i = 0; i < n; i++){
        index[inorder[i]] = i;
    }
    return dfs(preorder, index, 0, n, 0);
}

// 先序遍历（验证用，应等于输入的 preorder）
void printPreorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

// 中序遍历（验证用，应等于输入的 inorder）
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main(){
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    TreeNode* root = buildTree(preorder, inorder);
    cout << "先序";
    printPreorder(root);
    cout << "\n中序";
    printInorder(root);
    return 0;
}