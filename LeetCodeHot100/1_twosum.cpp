/*
1.两数之和

给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
你可以按任意顺序返回答案。
*/
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

vector<int> twosum(vector<int> nums, int k){
    unordered_map<int, int> mp;     // key为数值，value为下表
    for(int i = 0; i < nums.size(); i++){
        if(mp.count(k - nums[i])) return {i, mp[k - nums[i]]};
        mp[nums[i]] = i;
    }
    return {};
}

int main(){
    vector<int> nums = {2, 7, 11, 15};
    vector<int> ans = twosum(nums, 9);
    for(int num : ans) cout << num << " ";
    return 0;
}