/*
给定一系列操作（长度为n的数组），实现一个先进先出环形队列类，包含以下功能：
1. 固定容量c
2. 输入一系列操作：
- 如果该数为非负数，如果队列未满，把该数放入队列中；如果队列已满，丢弃该数，上溢出数加一；
- 如果该数为-1，如果队列不为空，则弹出最早放入的元素；如果队列为空，下溢出数加一。

输入描述：
第一行为容量和长度
第二行为n个操作数

输出描述：
第一行输出依次成功弹出的元素
第二行输出三个数，分别为上溢出数、下溢出数、最终队列的元素个数

示例：
输入：
3 9
1 2 3 4 -1 5 -1 -1 -1
输出：
1 2 3 5
1 0 0 
*/
#include <iostream>
#include <vector>
using namespace std;

class CircularQueue{
private:
    vector<int> buffer;
    int capacity;
    int head;
    int tail;
    int count;
    int overflow_count;
    int underflow_count;

public:
    CircularQueue(int c) : capacity(c), head(0), tail(0), count(0), overflow_count(0), underflow_count(0) {
        buffer.resize(c);
    }
    void push(int val){
        if(count == capacity){
            overflow_count++;
        }else{
            buffer[tail] = val;
            tail = (tail + 1) % capacity;
            count++;
        }
    }
    bool pop(int &val){
        if(count == 0){
            underflow_count++;
            return false;
        }else{
            val = buffer[head];
            head = (head + 1) % capacity;
            count--;
            return true;
        }
    }
    int get_overflow_count() {return overflow_count;}
    int get_underflow_count() {return underflow_count;}
    int size() {return count;}
};

int main(){
    int c, n;
    cin >> c >> n;
    CircularQueue q(c);
    vector<int> nums;
    for(int i = 0; i < n; i++){
        int op;
        cin >> op;
        if(op >= 0) q.push(op);
        else if(op == -1){
            int val;
            if(q.pop(val)) nums.push_back(val);
        }
    }
    for(int i = 0; i < nums.size(); i++) cout << nums[i] << " ";
    cout << "\n";
    cout << q.get_overflow_count() << q.get_underflow_count() << q.size() << "\n";
    return 0;
}
