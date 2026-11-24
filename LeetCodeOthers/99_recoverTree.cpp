/*
9. 恢复二叉搜索树

给你二叉搜索树的根节点 root ，该树中的 恰好 两个节点的值被错误地交换。请在不改变其结构的情况下，恢复这棵树 。
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

TreeNode *first = nullptr;
TreeNode *second = nullptr;
TreeNode *prevNode = nullptr;

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

void inorder(TreeNode* root) {
    if(!root) return;
    inorder(root->left);
    // 检查是否出现逆序对，统一判断方式为前一个节点值大于当前节点值
    if(prevNode && prevNode->val > root->val) {
        // 第一处逆序对的第一个节点，first为前一个节点
        if(!first) first = prevNode;
        // second需要每次更新直至找到最后一个出现的逆序对，second为当前节点
        second = root;
    }
    prevNode = root;
    inorder(root->right);
}

void recoverTree(TreeNode* root) {
    inorder(root);
    if(first && second) swap(first->val, second->val);
}

int main() {
    vector<string> nodes = {"3", "1", "4", "null", "null", "2"};
    TreeNode* root = buildTreeNode(nodes);
    printLevelOrder(root);
    cout << "\n";
    recoverTree(root);
    printLevelOrder(root);
    return 0;
}