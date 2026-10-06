/*
155. 最小栈

设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:
MinStack() 初始化堆栈对象。
void push(int value) 将元素 value 推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素
*/
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

class MinStack{
    stack<pair<int, int>> st;
public:
    MinStack(){
        st.emplace(0, INT_MAX);
    }
    void push(int value){
        st.emplace(value, min(getMin(), value));
    }
    void pop(){
        st.pop();
    }
    int top(){
        return st.top().first;
    }
    int getMin(){
        return st.top().second;
    }
};

int main(){
    MinStack ms;
    ms.push(-2);
    ms.push(0);
    ms.push(-3);
    cout << ms.getMin() << "\n";
    ms.pop();
    cout << ms.top() << "\n";
    cout << ms.getMin() << "\n";
    return 0;
}