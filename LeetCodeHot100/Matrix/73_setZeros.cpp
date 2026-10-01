/*
73. 矩阵置零

给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。
*/
#include <vector>
#include <iostream>
using namespace std;

void setZeros(vector<vector<int>>& matrix){
    int m = matrix.size(), n = matrix[0].size();
    bool col0 = false;
    for(int i = 0; i < m; i++){
        if(matrix[i][0] == 0) col0 = true;
        for(int j = 1; j < n; j++){
            if(matrix[i][j] == 0){
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for(int i = m - 1; i >= 0; i--){
        for(int j = n - 1; j > 0; j--){
            if(matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
        }
        if(col0) matrix[i][0] = 0;
    }
}

int main(){
    vector<vector<int>> matrix = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1 ,5}};
    setZeros(matrix);
    for(auto& nums : matrix){
        for(int num : nums) cout << num << " ";
        cout << "\n";
    }
    return 0;
}