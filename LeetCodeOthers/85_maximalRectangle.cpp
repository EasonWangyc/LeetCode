/*
85. 最大矩形

给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
*/
#include <bits/stdc++.h>
using namespace std;

int largestRectangleArea(vector<int>& grid) {
    // grid.push_back(-1); // 确保原最后一个元素被计算到
    stack<int> st;
    st.push(-1);
    int n = grid.size(), ans = 0;
    for(int r = 0; r < n; r++) {
        int h = grid[r];
        while(st.size() > 1 && grid[st.top()] >= h) {
            int i = st.top();
            st.pop();
            int l = st.top();
            ans = max(ans, grid[i] * (r - l - 1));
        }
        st.push(r);
    }
    return ans;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    int n = matrix[0].size();
    vector<int> height(n + 1); // 等价于上述函数中的push_back(-1)
    int ans = 0;
    for(auto& row : matrix) {
        for(int j = 0; j < n; j++) {
            if(row[j] == '0') height[j] = 0;
            else height[j]++;
        }
        ans = max(ans, largestRectangleArea(height));
    }
    return ans;
}

int main() {
    vector<vector<char>> matrix = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
    cout << maximalRectangle(matrix) << "\n";
    return 0;
}