#include <iostream>
#include <vector>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB){
    ListNode* p = headA, *q = headB;
    while(p != q){
        p = p ? p->next : headB;//若p不为空，则p指向下一个节点；否则，p指向headB
        q = q ? q->next : headA;//若q不为空，则q指向下一个节点；否则，q指向headA
    }
    return p;
}

int main(){
    ListNode* common = new ListNode(8);
    common -> next = new ListNode(4);
    common -> next -> next = new ListNode(5);

    //A前半
    ListNode* headA = new ListNode(4);
    headA -> next = new ListNode(1);
    headA -> next -> next = common;

    //B前半
    ListNode* headB = new ListNode(5);
    headB -> next = new ListNode(6);
    headB -> next -> next = new ListNode(1);
    headB -> next -> next -> next = common;

    ListNode* ans = getIntersectionNode(headA, headB);
    cout << "Intersected at '" << ans -> val << "'\n";
    return 0;
}