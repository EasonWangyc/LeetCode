/*
118. 杨辉三角

给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
在「杨辉三角」中，每个数是它左上方和右上方的数的和。
*/
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> generate(int numRows){
    vector<vector<int>> ans(numRows);
    for(int i = 1; i < numRows; i++){
        ans[i].resize(i + 1, 1);
        for(int j = 1; j < i; j++) ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
    }
    return ans;
}

int main(){
    vector<vector<int>> ans = generate(4);
    for(auto& nums : ans){
        for(int x : nums) cout << x << " ";
        cout << "\n";
    }
    return 0;
}