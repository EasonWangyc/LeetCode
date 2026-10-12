/*
105. 从前序与中序遍历序列构造二叉树

给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

提示：不包含重复元素。

思路：
先序遍历的第一个元素一定是根节点。
在中序遍历中找到这个根节点的位置，左边是左子树，右边是右子树，从而得到左子树的大小 left_size。
再根据 left_size 把先序遍历切成 [左子树][右子树]，递归构造左右子树。
*/
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
先序遍历 preorder:  [根节点 | 左子树 (left_size 个) |            右子树      ]
                    pre_l    pre_l+1      pre_l+1+left_size      pre_r

中序遍历 inorder:   [    左子树 (left_size 个)    | 根节点 |       右子树      ]
                    in_l                           k      k+1
*/

TreeNode* dfs(vector<int>& preorder, unordered_map<int, int>& index, 
              int pre_l, int pre_r, int in_l){
    if(pre_l == pre_r) return nullptr;
    int k = preorder[pre_l];
    int left_size = index[k] - in_l;
    TreeNode* left = dfs(preorder, index, pre_l + 1, pre_l + 1 + left_size, in_l);
    TreeNode* right = dfs(preorder, index, pre_l + 1 + left_size, pre_r, index[k] + 1);
    TreeNode* root = new TreeNode(k);
    root->left = left;
    root->right = right;
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder){
    unordered_map<int, int> mp;
    int n = preorder.size();
    for(int i = 0; i < n; i++) mp[inorder[i]] = i;
    return dfs(preorder, mp, 0, n, 0);
}

void printlevelOrder(TreeNode* root){
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
    for(int i = 0; i < result.size(); i++) cout << result[i] << " ";
    cout << "\n";
}

int main(){
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    TreeNode* root = buildTree(preorder, inorder);
    printlevelOrder(root);
    return 0;
}