/*
55. 跳跃游戏

给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool canJump(vector<int>& nums){
    int n = nums.size();
    int m = 0;
    for(int i = 0; i < n; i++){
        if(i > m) return false;
        m = max(m, nums[i] + i);
    }
    return true;
}

int main(){
    vector<int> nums = {3, 2, 1, 0, 4};
    cout << boolalpha << canJump(nums) << "\n";
    return 0;
}