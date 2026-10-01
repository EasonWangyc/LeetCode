/*
240. 搜索二维矩阵Ⅱ

编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
*/
#include <vector>
#include <iostream>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target){
    int m = matrix.size(), n = matrix[0].size();
    int i = 0, j = n - 1;
    while(i < m && j >= 0){
        if(matrix[i][j] > target) j--;
        else if(matrix[i][j] < target) i++;
        else return true;
    }
    return false;
}

int main(){
    vector<vector<int>> matrix = {{1, 4, 7, 11, 15},
                                  {2, 5, 8, 12, 19},
                                  {3, 6, 9, 16, 22},
                                  {10, 13, 14, 17, 24},
                                  {18, 21, 23, 26, 30}};
    cout << boolalpha << searchMatrix(matrix, 5) << "\n";
    return 0;
}