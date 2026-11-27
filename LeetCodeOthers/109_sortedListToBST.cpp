/*
109. 有序链表转换二叉搜索树

给定一个单链表的头节点  head ，其中的元素 按升序排序 ，将其转换为 平衡 二叉搜索树。
*/
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head, *fast = head, *pre = nullptr;
    while(fast && fast->next) {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if(pre) pre->next = nullptr;
    return slow;
}

TreeNode* sortedListToBST(ListNode* head) {
    if(!head) return nullptr;
    if(!head->next) return new TreeNode(head->val);
    ListNode* middle = findMiddle(head);
    TreeNode* left = sortedListToBST(head);
    TreeNode* right = sortedListToBST(middle->next);
    return new TreeNode(middle->val, left, right);
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
    for(int i = 0; i < (int)result.size(); i++) cout << result[i] << " ";
    cout << "\n";
}

int main() {
    ListNode* head = new ListNode(-10);
    head->next = new ListNode(-3);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(9);
    TreeNode* root = sortedListToBST(head);
    printLevelOrder(root);
    return 0;
}