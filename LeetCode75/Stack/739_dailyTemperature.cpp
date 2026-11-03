/*
739. 每日温度

给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> dailyTemperature(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> answer(n, 0);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && temperatures[i] > temperatures[st.top()]) {
            answer[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    return answer;
}

int main() {
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> ans = dailyTemperature(temperatures);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}