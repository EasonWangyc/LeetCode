/*
20. 有效的括号

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;

bool isValidBrackets(string s){
    unordered_map<char, char> mp = {{')', '('}, {'}', '{'}, {']', '['}};
    stack<char> st;
    int n = s.length();
    if(n % 2 != 0) return false;
    for(char c : s){
        if(!mp.count(c)){
            st.push(c);
        }else{
            if(st.empty() || st.top() != mp[c]) return false;
            st.pop();
        }
    }
    return st.empty();
}

int main(){
    string s = "([]})";
    cout << isValidBrackets(s) << "\n";
    return 0;
}