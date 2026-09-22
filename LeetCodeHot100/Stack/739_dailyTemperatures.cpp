/*
给定一个整数数组 `temperatures`，表示每天的温度，返回一个数组 `answer`，其中 `answer[i]` 是指从第 `i` 天开始，经过多少天后温度会升高。如果之后都不会升高，则在该位置用 0 来代替。

示例：
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]

思路：每次入栈判断，如果当前温度比栈顶温度高，则说明栈顶温度找到了比它高的温度，出栈并计算下标对应的天数，接着继续判断栈顶元素，直到栈为空或者当前温度不再比栈顶温度高，然后将当前下标入栈，作为新的栈顶元素。观察栈的元素，可以发现是一个单调栈，即元素下标对应的温度是递减的。

注意：每次循环需要一直判断当前温度是否比栈顶温度高，直到栈为空或者当前温度不再比栈顶温度高为止，所以内层需要使用`while`而不是`if`。
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperatures(vector<int>& nums){
    int n = nums.size();
    vector<int> ans(n, 0);
    stack<int> st;
    for(int i = 0;i < n; i++){
        while(!st.empty() && nums[i] > nums[st.top()]){
            int pre = st.top();
            st.pop();
            ans[pre] = i - pre;
        }
        st.push(i);
    }
    return ans;
}

int main(){
    vector<int> nums = {73,74,75,71,69,72,76,73};
    vector<int> ans = dailyTemperatures(nums);
    for(int an : ans){
        cout << an << " ";
    }
    cout << "\n";
    return 0;
}