/*
61. 旋转链表

给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。
*/
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    ListNode* cur = head;
    int n = 0;
    while(cur) {
        n++;
        cur = cur->next;
    }
    k %= n;
    if(k == 0) return head;
    ListNode* fast = head, *slow = head;
    while(k--) fast = fast->next;
    while(fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* new_head = slow->next;
    slow->next = nullptr;
    fast->next = head;
    return new_head;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* ans = rotateRight(head, 2);
    while(ans) {
        cout << ans->val << " ";
        ans = ans->next;
    }
    cout << "\n";
    return 0;
}