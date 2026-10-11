/*
146. LRU 缓存

请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：

LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存

int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。

void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。

函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

       ┌────────────────────────────────────────────────────────┐
       ▼                                                        │
   [ dummy ] <═════> [ Node 1 ] <═════> ... <═════> [ Node K ] ─┘
     (哨兵)             (最新使用)                    (最久未使用)
*/
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Node{
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k = 0, int v = 0) : key(k), value(v) {}
};

class LRUCache {
private:
    int capacity;
    Node* dummy;
    unordered_map<int, Node*> key_to_node;

    void remove(Node* x){
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    void push_front(Node* x){
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;      // dummy->next = x
        x->next->prev = x;      // 原第一个节点的prev为x
    }

    Node* get_node(int key){
        auto it = key_to_node.find(key); // 安全检查key是否存在
        if(it == key_to_node.end()) return nullptr;
        Node* node = it->second;
        remove(node);
        push_front(node);
        return node;
    }
public:
    LRUCache(int capacity) : capacity(capacity), dummy(new Node()){
        // 初始化自身为一个环形链表
        dummy->next = dummy;
        dummy->prev = dummy;
    }

    ~LRUCache() {
        Node* cur = dummy->next;
        while(cur != dummy){
            Node *nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        delete dummy;
    }
    
    int get(int key){
        Node* node = get_node(key);
        return node ? node->value : -1;
    }

    void put(int key, int value){
        Node* node = get_node(key);
        // key原本存在，更新value
        if(node){
            node->value = value;
            return ;
        }
        // key原本不存在
        key_to_node[key] = node = new Node(key, value);
        push_front(node);
        int n = key_to_node.size();
        if(n > capacity){
            Node* back_node = dummy->prev;      // 由于是双向链表直接得到最后一个节点，即为dummy->prev
            key_to_node.erase(back_node->key);  // 使用erase删除key为key的哈希表元素
            remove(back_node);
            delete back_node;
        }
    }
};

int main(){
    LRUCache lru(2);
    lru.put(1, 10);
    lru.put(2, 20);
    cout << lru.get(1) << "\n";
    lru.put(3, 30); // 2被淘汰
    cout << lru.get(2) << "\n";
    cout << lru.get(1) << " " << lru.get(3) <<"\n";
    return 0;
}