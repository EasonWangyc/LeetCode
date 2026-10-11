/*
19. 删除链表的倒数第 N 个结点

给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
*/
#include <vector>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* buildList(const vector<int>& nums){
    ListNode dummy(0);
    ListNode* head = &dummy;
    for(int num : nums){
        head->next = new ListNode(num);
        head = head->next;
    }
    return dummy.next;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode *left = head, *right = head;
    while(n--) right = right->next;
    // 因为要处理left前一个节点，所以right要停在最后一个节点
    // 以12345和n=2为例，right第一次停在3，然后停在5，此时left停在3
    while(right->next){   
        left = left->next;
        right = right->next;
    }
    ListNode *toDelete = left->next;
    left->next = left->next->next;
    delete toDelete;
    return dummy.next;
}

int main(){
    vector<int> nums = {1, 2, 3, 4, 5};
    int n = 2;
    ListNode* head = buildList(nums);
    head = removeNthFromEnd(head, n);
    while(head){
        cout << head->val << " ";
        head = head->next;
    }
    cout << "\n";
    return 0;
}