/*
234. 回文链表

给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。
*/
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* pre = nullptr, *cur = head;
    while (cur) {
        ListNode* nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

// 找到链表中间节点
ListNode* middleNode(ListNode* head){
    ListNode *slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

bool isPalindrome(ListNode* head){
    // 奇数情况1 2 3 2 1，slow为3，后半段反转为1 2 3
    // 偶数情况1 2 2 1，slow为第二个2，后半段反转为1 2
    ListNode *mid = middleNode(head);
    ListNode *rev = reverseList(mid);
    while(rev){
        if(rev->val  != head->val) return false;
        rev = rev->next;
        head = head->next;
    }
    return true;
}

int main(){
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);

    cout << boolalpha << isPalindrome(head) << "\n";
    return 0;
}