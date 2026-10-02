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
    auto left = mergeKLists(lists, i, i + m / 2);
    auto right = mergeKLists(lists, i + m / 2, j);
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