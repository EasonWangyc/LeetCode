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
    ListNode* ans = &dummy;
    while(l1 && l2){
        if(l1->val > l2->val){
            ans->next = l2;
            l2 = l2->next;
        }
        else{
            ans->next = l1;
            l1 = l1->next;
        }
        ans = ans->next;
    }
    ans->next = l1 ? l1 : l2;//如果l1和l2长度不一样，剩下的部分直接接在后面
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