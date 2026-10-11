/*
21. 合并两个有序链表

将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
*/
#include <vector>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(!l1) return l2;
    if(!l2) return l1;
    ListNode dummy(0);
    ListNode* head = &dummy;
    while(l1 && l2){
        if(l1->val > l2->val){
            head->next = l2;
            l2 = l2->next;
        }else{
            head->next = l1;
            l1 = l1->next;
        }
        head = head->next;
    }
    head->next = l1 ? l1 : l2;
    return dummy.next;
}

ListNode* buildList(const vector<int>& nums){
    ListNode dummy(0);
    ListNode* head = &dummy;
    for(int num : nums){
        head->next = new ListNode(num);
        head = head->next;
    }
    return dummy.next;
}

int main(){
    vector<int> nums1 = {1, 2, 4};
    vector<int> nums2 = {1, 3, 4};
    ListNode* l1 = buildList(nums1);
    ListNode* l2 = buildList(nums2);
    ListNode* ans = mergeTwoLists(l1, l2);
    while(ans){
        cout << ans->val << " ";
        ans = ans->next;
    }
    cout << "\n";
    return 0;
}