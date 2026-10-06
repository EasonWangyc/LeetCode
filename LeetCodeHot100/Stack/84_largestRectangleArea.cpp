/*
84. 柱状图中最大的矩形

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

思路：双指针+单调栈，遍历右指针，每次去找他和前面元素能够构成的最大面积，其实就是找左侧第一个小于它的元素。
*/
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int largestRectangleArea(vector<int>& heights){
    heights.push_back(-1);
    stack<int> st;
    st.push(-1);
    int n = heights.size(), ans = 0;
    for(int r = 0; r < n; r++){
        int h = heights[r];
        while(st.size() > 1 && heights[st.top()] >= h){
            int i = st.top();
            st.pop();
            int l = st.top();
            ans = max(ans, heights[i] * (r - l - 1));
        }
        st.push(r);
    }
    return ans;
}

int main(){
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << largestRectangleArea(heights) << "\n";
    return 0;
}