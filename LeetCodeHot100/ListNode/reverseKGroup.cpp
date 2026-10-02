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
    ListNode* pre = nullptr;
    ListNode* cur = head;
    for(; n >= k; n -= k){
        for(int i = 0; i < k; i++){
            ListNode* nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        ListNode* nxt = p0->next;//保存当前段的头结点
        p0->next->next = cur;//当前段的头结点指向下一段的头结点
        p0->next = pre;//当前段的头结点指向反转后的头结点
        p0 = nxt;//移动p0到下一段的前一个节点
    }
    return dummy.next;
    //以[1,2,3,4]且k=3为例：
    //初始化：p0指向dummy，pre=nullptr，cur=1  dummy->1->2->3->4->nullptr
    //第一次循环：1指向nullptr，pre=1，cur=2    1->nullptr,2->3->4->nullptr
    //第二次循环：2指向1，pre=2，cur=3          2->1->nullptr,3->4->nullptr
    //第三次循环：3指向2，pre=3，cur=4          3->2->1->nullptr,4->nullptr
    //nxt = p0->next指向1                    dummy->1，保留1
    //将1指向4                                1->4->nullptr  
    //将p0->next指向3                         dummy->3->2->1->4->nullptr
    //将p0移动到1                             p0更新为1，准备下一段的反转
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