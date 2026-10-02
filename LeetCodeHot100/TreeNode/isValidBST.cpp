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


bool isValidBST(TreeNode* root, long long min = LLONG_MIN){
    if(root == nullptr) return true;
    if(!isValidBST(root->left, min)) return false;// 先判断左子树是否合法，如果不合法直接返回 false
    if(root->val <= min) return false;// 如果当前节点的值不大于前一个节点的值，说明不是二叉搜索树，返回 false
    min = root->val;
    return isValidBST(root->right, min);// 最后判断右子树是否合法，如果不合法直接返回 false，否则返回 true
}

int main() {
    vector<string> nodes = {"5", "1", "4", "null", "null", "3", "6"};
    TreeNode* root = buildTreeNode(nodes);
    cout << boolalpha << isValidBST(root) << endl;
    return 0;
}