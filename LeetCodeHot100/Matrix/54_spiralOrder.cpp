/*
54. 螺旋矩阵

给你一个m行n列的矩阵matrix，请按照顺时针螺旋顺序，返回矩阵中的所有元素。
*/
#include <vector>
#include <iostream>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix){
    vector<int> ans;
    if(matrix.empty()) return ans;
    int u = 0;
    int d = matrix.size() - 1;
    int l = 0;
    int r = matrix[0].size() - 1;
    while(true){
        for(int i = l; i <= r; i++) ans.push_back(matrix[u][i]);
        if(++u > d) break;
        for(int i = u; i <= d; i++) ans.push_back(matrix[i][r]);
        if(--r < l) break;
        for(int i = r; i >= l; i--) ans.push_back(matrix[d][i]);
        if(--d < u) break;
        for(int i = d; i >= u; i--) ans.push_back(matrix[i][l]);
        if(++l > r) break;
    }
    return ans;
}

int main(){
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<int> nums = spiralOrder(matrix);
    for(auto& x : nums) cout << x << " ";
    cout << "\n";
    return 0;
}