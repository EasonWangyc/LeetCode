/*
48. 旋转图像

给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void rotate(vector<vector<int>>& matrix){
    int n = matrix.size();
    // 90°旋转 = 对角线交换 + 每行反转
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++) swap(matrix[i][j], matrix[j][i]);
    }
    for(int i = 0; i < n; i++) reverse(matrix[i].begin(), matrix[i].end()); 
}

int main(){
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    rotate(matrix);
    for(auto& nums : matrix){
        for(auto& num : nums) cout << num << " ";
        cout << "\n";
    }
    return 0;
}