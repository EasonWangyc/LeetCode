/*
92. 反转链表Ⅱ

给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
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

ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (!head || !head->next || left == right) return head;
    ListNode dummy(0);
    dummy.next = head;
    // (12345,2,4)为例，停止时l在1，pre在2，cur在3
    ListNode* l = &dummy;
    for(int i = 0; i < left - 1; i++) l = l->next;
    ListNode* pre = l->next;
    ListNode* r = pre;
    ListNode* cur = pre->next;
    // 停止时pre在4，cur在5
    for(int i = 0; i < right - left; i++) {
        ListNode* nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    l->next = pre;
    r->next = cur;
    return dummy.next;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    reverseBetween(head, 2, 4);
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << "\n";
    return 0;
}