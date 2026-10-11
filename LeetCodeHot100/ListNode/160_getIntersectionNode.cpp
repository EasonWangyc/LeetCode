/*
160. 相交链表

给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
*/
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB){
    ListNode *p = headA, *q = headB;
    while(p != q){
        p = p != nullptr ? p->next : headB;
        q = q != nullptr ? q->next : headA;
    }
    return p;
}

int main(){
    ListNode* common = new ListNode(8);
    common->next = new ListNode(4);
    common->next->next = new ListNode(5);
    ListNode* headA = new ListNode(4);
    headA->next = new ListNode(1);
    headA->next->next = common;
    ListNode* headB = new ListNode(5);
    headB->next = new ListNode(6);
    headB->next->next = new ListNode(1);
    headA->next->next->next = common;
    cout << getIntersectionNode(headA, headB)->val << "\n";
    return 0;
}