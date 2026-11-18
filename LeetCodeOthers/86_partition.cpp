/*
86. 分隔链表

给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

你应当 保留 两个分区中每个节点的初始相对位置。
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

ListNode* partition(ListNode* head, int x) {
    ListNode smaller_dummy(0), larger_dummy(0);
    ListNode *smaller = &smaller_dummy, *larger = &larger_dummy;
    while(head) {
        if(head->val < x) {
            smaller->next = head;
            smaller = smaller->next;
        }else {
            larger->next= head;
            larger = larger->next;
        }
        head = head->next;
    }
    smaller->next = larger_dummy.next;
    larger->next = nullptr;
    return smaller_dummy.next;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(4);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(2);
    ListNode* cur = partition(head, 3);
    while(cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << "\n";
    return 0;
}