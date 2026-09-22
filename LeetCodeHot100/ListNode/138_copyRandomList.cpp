/*
给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

返回复制链表的头节点。

用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
你的代码只接受原链表的头节点 head 作为传入参数。

示例：
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

思路：在原链表的每个节点后复制粘贴一个新节点，然后再处理随机指针，最后将新旧节点分离。
*/
#include <vector>
#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val){
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

Node* copyRandomList(Node* head){
    if(!head) return nullptr;
    //核心是在原链表的每个节点后面复制粘贴一个新节点
    //第一步，复制，不拷贝随机节点
    for(Node* cur = head; cur; cur = cur->next->next){
        Node* next = cur->next;
        cur->next = new Node(cur->val); //创建新节点
        cur->next->next = next;         //复原指向
    }
    //将新节点的random对应过去
    for(Node* cur = head; cur; cur = cur->next->next){
        if(cur->random) cur->next->random = cur->random->next;
        //默认指向nullptr，无需处理
    }
    Node dummy(0);
    Node* tail = &dummy;
    for(Node* cur = head; cur; ){
        Node* copy = cur->next;
        tail->next = copy;
        cur->next = copy->next;
        cur = cur->next;//相当于cur = cur->next->next
        tail = tail->next;
    }
    return dummy.next;
}

int main(){
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->random = head->next;
    head->next->random = head->next;
    head->next->next->random = head;
    
    Node* ans = copyRandomList(head);
    cout << ans->val << " " << ans->next->val << endl;
    cout << ans->random->val << " " << ans->next->random->val << endl;
    return 0;
}