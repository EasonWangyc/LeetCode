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

ListNode* middleNode(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

bool isPalindrome(ListNode* head){
    ListNode* mid = middleNode(head);
    ListNode* rev = reverseList(mid);//反转前半段
    while(rev){
        if(rev->val != head->val) return false;
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

    cout << (isPalindrome(head) ? "true" : "false")  << "\n";
    return 0;
}