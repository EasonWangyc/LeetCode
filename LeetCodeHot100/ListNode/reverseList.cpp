#include <iostream>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head){
    ListNode* pre = nullptr;
    ListNode* cur = head;
    while(cur){
        ListNode* nxt = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nxt;
    }
    return pre;
}

void printList(ListNode* head){
    while(head){
        cout << head->val << " ";
        head = head->next;
    }
    cout << "\n";
}

int main(){
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    ListNode* n5 = new ListNode(5);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    ListNode* ans = reverseList(n1);
    printList(ans);
    return 0;
}