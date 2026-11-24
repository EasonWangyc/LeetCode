/*
103. 二叉树的锯齿形层序遍历

给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
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
    for(int i = 0; i < result.size(); i++) cout << result[i] << " ";
    cout << "\n";
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if(!root) return {};
    queue<TreeNode*> q;
    vector<vector<int>> ans;
    q.push(root);
    while(!q.empty()) {
        vector<int> ref;
        // 得到初始队列的长度，相当于自动实现“层”
        for(int n = q.size(); n--;) {
            auto node = q.front();
            q.pop();
            ref.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        if(ans.size() % 2) reverse(ref.begin(), ref.end());
        ans.push_back(move(ref));
    }
    return ans;
}

int main() {
    vector<string> nodes = {"3", "9", "20", "null", "null", "15", "7"};
    TreeNode* root = buildTreeNode(nodes);
    vector<vector<int>> ans = zigzagLevelOrder(root);
    for(auto& it : ans) {
        for(int num : it) cout << num << " ";
        cout << "\n";
    }
    return 0;
}