/*
25. K 个一组翻转链表

给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
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

ListNode* reverseKGroup(ListNode* head, int k){
    int n = 0;
    for(ListNode* cur = head; cur; cur = cur->next) n++;
    ListNode dummy(0);
    dummy.next = head;
    ListNode* p0 = &dummy;
    ListNode* cur = head;
    ListNode* pre = nullptr;
    for(; n >= k; n -= k){
        for(int i = 0; i < k; i++){
            ListNode* nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
            // 结束时cur在下一段的开始
        }
        // 以12345，n为2为例->21435
        // p0在哨兵，nxt在1，cur为3，pre为2
        ListNode* nxt = p0->next;
        p0->next->next = cur;   // 1->3
        p0->next = pre;         // dummy->2
        p0 = nxt;               // pre变为当前段的尾节点1
    }
    return dummy.next;
}

int main(){
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    ListNode* head = buildList(nums);
    ListNode* ans = reverseKGroup(head, 3);
    while(ans){
        cout << ans->val << " ";
        ans = ans->next;
    }
    cout << "\n";
    return 0;
}