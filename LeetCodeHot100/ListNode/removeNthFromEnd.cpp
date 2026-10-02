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
    ListNode* left = &dummy;
    ListNode* right = &dummy;
    while(n--) right = right->next;
    while(right->next){
        left = left->next;
        right = right->next;
    }
    ListNode* toDelete = left->next;
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