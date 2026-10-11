/*
148. 排序链表

给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
*/
#include <vector>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
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
// 切分链表为两个部分
ListNode* middleNode(ListNode* head) {
    ListNode* pre = head;
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast && fast->next){
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = nullptr;
    return slow;
}

// 升序合并
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
    ListNode dummy(0);
    ListNode* cur = &dummy;
    while(l1 && l2){
        if(l1->val < l2->val){
            cur->next = l1;
            l1 = l1->next;
        }else{
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy.next;
}

// 递归解决
ListNode* sortList(ListNode* head){
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* head2 = middleNode(head);
    head = sortList(head);
    head2 = sortList(head2);
    return mergeTwoLists(head, head2);
}

int main(){
    vector<int> nums = {-1, 5, 3, 4, 0};
    ListNode* head = buildList(nums);
    ListNode* ans = sortList(head);
    for(ListNode* cur = ans; cur; cur = cur->next){
        cout << cur->val << " ";
    }
    cout << endl;
    return 0;
}