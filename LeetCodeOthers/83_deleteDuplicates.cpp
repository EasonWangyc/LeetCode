/*
83. 删除排序链表中的重复元素

给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。
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

ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while(cur->next) {
        if(cur->val == cur->next->val) {
            ListNode* nxt = cur->next;
            cur->next = nxt->next;
            delete nxt;
        }else cur = cur->next;
    }
    return head;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(3);
    deleteDuplicates(head);
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << "\n";
    return 0;
}