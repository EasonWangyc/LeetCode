/*
给你一个链表的头节点 head ，判断链表中是否有环。如果链表中存在环，则返回 true 。 否则，返回 false 。

示例：
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。

思路：快慢指针，快指针每次移动两步，慢指针每次移动一步，如果链表中存在环，那么快指针最终会追上慢指针；如果链表中不存在环，快指针会先到达链表末尾。
*/
#include <iostream>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode *head) {
    if(!head) return false;
    ListNode* slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}

ListNode* bulidList(const vector<int>& nums){
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for(int num : nums){
        tail->next = new ListNode(num);
        tail = tail->next;
    }
    return dummy.next;
}

int main(){
    ListNode* head = bulidList({3, 2, 0, -4});
    head->next->next->next->next = head->next; // Create a cycle
    cout << (hasCycle(head) ? "true" : "false") << "\n";
    return 0;
}