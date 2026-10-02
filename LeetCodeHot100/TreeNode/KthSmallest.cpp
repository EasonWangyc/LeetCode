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

TreeNode* buildTreeNode(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") {
        return nullptr;
    }

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    int index = 1;

    while (!nodeQueue.empty() && index < static_cast<int>(nodes.size())) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();

        if (index < static_cast<int>(nodes.size()) && nodes[index] != "null") {
            current->left = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(current->left);
        }
        ++index;

        if (index < static_cast<int>(nodes.size()) && nodes[index] != "null") {
            current->right = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(current->right);
        }
        ++index;
    }

    return root;
}

void dfs(TreeNode* node, int& k, int& ans){
    if(node == nullptr || k <= 0) return;
    dfs(node->left, k, ans);
    k--;
    if(k == 0){
        ans = node->val;
        return;
    }
    dfs(node->right, k, ans);
}

int main(){
    vector<string> nodes = {"5", "3", "6", "2", "4", "null", "null", "1"};
    TreeNode* root = buildTreeNode(nodes);
    int k = 3;
    int ans = 0;
    dfs(root, k, ans);
    cout << ans << endl;
    return 0;
}