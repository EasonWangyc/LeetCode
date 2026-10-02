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
        ListNode* nxt = cur->next;
        ListNode* nxtnxt = cur->next->next;

        pre->next = nxt;
        nxt->next = cur;
        cur->next = nxtnxt;

        pre = cur; // 更新pre，注意是cur
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