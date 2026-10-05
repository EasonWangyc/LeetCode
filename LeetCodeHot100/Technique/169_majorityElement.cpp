/*
169. 多数元素

给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。

进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// O(nlogn)时间
int majorityElement1(vector<int>& nums){
    sort(nums.begin(), nums.end());
    int i = nums.size() / 2;
    return nums[i];
}

// O(n)时间，O(1)空间
int majorityElement2(vector<int>& nums){
    int ans = 0, hp = 0;
    for(int x : nums){
        if(hp == 0){
            ans = x;
            hp = 1;
        }else{
            hp += (ans == x) ? 1 : -1;
        }
    }
    return ans;
}

int main(){
    vector<int> nums = {1, 1, 2, 2, 2};
    cout << majorityElement1(nums) << majorityElement2(nums) << "\n";
    return 0; 
}