/*
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

示例：
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。

思路：快慢指针，当快慢指针相遇时，快指针回到链表头部，慢指针保持在相遇位置，然后两个指针每次移动一步，当它们再次相遇时，相遇点就是链表入环的第一个节点。
*/
#include <iostream>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* detectCycle(ListNode *head) {
    if(!head) return nullptr;
    ListNode* slow = head, *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            fast = head;
            while(slow != fast){
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return nullptr;
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
    cout << detectCycle(head)->val << "\n";
    return 0;
}