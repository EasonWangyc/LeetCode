/*
283.移动零

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
请注意 ，必须在不复制数组的情况下原地对数组进行操作。
*/
#include <iostream>
#include <vector>
using namespace std;

void moveZeros(vector<int>& nums){
    int stack_size = 0;
    for(int x : nums){
        if(x) nums[stack_size++] = x;
    }
    fill(nums.begin() + stack_size, nums.end(), 0);
}

int main(){
    vector<int> nums = {0, 1, 0, 3, 0, 0, 12, 0};
    moveZeros(nums);
    for(int num : nums) cout << num << " ";
    cout << "\n";
    return 0;
}