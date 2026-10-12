/*
108. 将有序数组转换为二叉搜索树

给你一个整数数组 nums ，其中元素已经按升序排列，请你将其转换为一棵 平衡 二叉搜索树。
*/
#include <vector>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* dfs(vector<int>& nums, int left, int right) {
    if(left == right) return nullptr;
    int m = (left + right) / 2;
    return new TreeNode(nums[m], dfs(nums, left, m), dfs(nums, m + 1, right));
}

TreeNode* sortedArrayToBST(vector<int>& nums){
    return dfs(nums, 0, nums.size());
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

int main() {
    vector<int> nums = {-10, -3, 0, 5, 9};
    TreeNode* root = sortedArrayToBST(nums);
    printlevelOrder(root);
    return 0;
}