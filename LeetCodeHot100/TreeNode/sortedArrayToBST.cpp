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
    int m = left + (right - left) / 2;
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

    while(!result.empty() && result.back() == "null"){
        result.pop_back();
    }

    for(int i = 0; i < static_cast<int>(result.size()); ++i){
        if(i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
}

int main() {
    vector<int> nums = {-10, -3, 0, 5, 9};
    TreeNode* root = sortedArrayToBST(nums);
    printlevelOrder(root);
    return 0;
}