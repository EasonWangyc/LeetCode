/*
116. 填充每个节点的下一个右侧节点指针

给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next) : val(_val), left(_left), right(_right), next(_next) {}
};

void printConnectedTree(Node* root) {
    if (!root) {
        cout << "\n";
        return;
    }
    Node* levelStart = root;
    bool firstElem = true;

    while (levelStart) {
        Node* cur = levelStart;
        while (cur) {
            if (!firstElem) cout << " ";
            cout << cur->val;
            firstElem = false;
            cur = cur->next;
        }
        // 每层结束输出 '#'
        cout << " #";
        levelStart = levelStart->left;
    }
    cout << "\n";
}

Node* connect(Node* root) {
    if(!root) return nullptr;
    vector<Node*> q = {root};
    while(!q.empty()) {
        vector<Node*> nxt;
        for(int i = 0; i < (int)q.size(); i++) {
            Node* node = q[i];
            if(i) q[i - 1]->next = node;
            if(node->left) nxt.push_back(node->left);
            if(node->right) nxt.push_back(node->right);
        }
        q = move(nxt);
    }
    return root;
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    connect(root);
    printConnectedTree(root);
    return 0;
}