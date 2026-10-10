/*
32. 最长有效括号

给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号 子串 的长度。
左右括号匹配，即每个左括号都有对应的右括号将其闭合的字符串是格式正确的，比如 "(()())"。
*/
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int longestValidParentheses(string s){
    stack<int> st;
    st.push(-1);
    int len = 0;
    int n = s.length();
    for(int i = 0; i < n; i++){
        if(s[i] == '(') st.push(i);
        else{
            st.pop();
            if(st.empty()) st.push(i); // 记录右括号 
            else len = max(len, i - st.top());
        }
    }
    return len;
}

int main(){
    string s = ")()(())))";
    cout << longestValidParentheses(s) << "\n";
    return 0;
}