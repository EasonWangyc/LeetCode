/*
24. 两两交换链表中的节点

给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
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

ListNode* swapPairs(ListNode* head){
    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy;
    ListNode* cur = head;
    while(cur && cur->next){
        ListNode *nxt = cur->next;
        ListNode *nxtnxt = cur->next->next;
        pre->next = nxt;
        nxt->next = cur;
        cur->next = nxtnxt;
        pre = cur;
        cur = nxtnxt;
    }
    return dummy.next;
}

int main(){
    vector<int> nums = {1, 2, 3, 4};
    ListNode* head = buildList(nums);
    ListNode* ans = swapPairs(head);
    while(ans){
        cout << ans->val << " ";
        ans = ans->next;
    }
    cout << "\n";
    return 0;
}