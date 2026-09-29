/*
1493. 删掉一个元素以后全为 1 的最长子数组

给你一个二进制数组 nums ，你需要从中删掉一个元素。
请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。
如果不存在这样的子数组，请返回 0 。
*/
#include <iostream>
#include <vector>
using namespace std;

int longestOnes(vector<int>& nums){
    int count = 0, ans = 0, left = 0;
    for(int right = 0; right < nums.size(); right++){
        count += 1 - nums[right];
        while(count > 1) count -= 1 - nums[left++];
        ans = max(ans, right - left); // 去掉0的个数
    }
    return ans;
}

int main(){
    vector<int> nums = {1, 1, 0, 1};
    cout << longestOnes(nums) << "\n";
    return 0;
}