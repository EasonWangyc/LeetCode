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

ListNode* mergeKLists(vector<ListNode*>& lists, int i, int j){
    int m = j - i;
    if(m == 0) return nullptr;
    if(m == 1) return lists[i];
    ListNode* left = mergeKLists(lists, i, i + m / 2);
    ListNode* right = mergeKLists(lists, i + m / 2, j);
    // 由于定义了上面两个边界条件的返回值，最终可以递归到两个链表的合并，总时间复杂度为O(logK)
    return mergeTwoLists(left, right);
}

int main(){
    vector<ListNode*> lists;
    lists.push_back(buildList({1, 4, 5}));
    lists.push_back(buildList({1, 3, 4}));
    lists.push_back(buildList({2, 6}));
    ListNode* ans = mergeKLists(lists, 0, lists.size());
    for(ListNode* cur = ans; cur; cur = cur->next){
        cout << cur->val << " ";
    }
    cout << endl;
    return 0;
}