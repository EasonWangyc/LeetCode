/*
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：
输入：链表1 = [2,4,3], 链表2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.

思路：用carry和sum记录进位和当前位的和，遍历两个链表，直到两个链表都遍历完，并且carry为0。每次计算sum = carry + (l1 ? l1->val : 0) + (l2 ? l2->val : 0)，然后更新carry = sum / 10，并将sum % 10作为当前位的值加入结果链表。
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

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* head = &dummy;
    int carry = 0;
    while(l1 || l2 || carry){
        int sum = carry;//记录进位
        if(l1){
            sum += l1->val;
            l1 = l1->next;
        }
        if(l2){
            sum += l2->val;
            l2 = l2->next;
        }
        carry = sum / 10;
        head->next = new ListNode(sum % 10);
        head = head->next;
    }
    return dummy.next;
}

int main(){
    vector<int> nums1 = {2, 4, 3};
    vector<int> nums2 = {5, 6, 4};
    ListNode* l1 = buildList(nums1);
    ListNode* l2 = buildList(nums2);
    ListNode* ans = addTwoNumbers(l1, l2);
    while(ans){
        cout << ans->val << " ";
        ans = ans->next;
    }
    cout << "\n";
    return 0;
}