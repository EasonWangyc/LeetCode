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

vector<vector<int>> levelOrder(TreeNode* root) {
    if(!root) return {};
    vector<vector<int>> ans;
    vector<TreeNode*> cur = {root};
    while(cur.size()){
        vector<TreeNode*> next;
        vector<int> vals;
        for(TreeNode* node : cur){
            vals.push_back(node->val);
            if(node->left) next.push_back(node->left);
            if(node->right) next.push_back(node->right);
        }
        cur = move(next);
        ans.push_back(move(vals));
    }
    return ans;
}

int main(){
    vector<string> nodes = {"3", "9", "20", "null", "null", "15", "7"};
    TreeNode* root = buildTreeNode(nodes);
    vector<vector<int>> result = levelOrder(root);

    for (const auto& level : result) {
        for (int val : level) {
            cout << val << " ";
        }
        cout << "\n";
    }
    return 0;
}