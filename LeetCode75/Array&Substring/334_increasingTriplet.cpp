/*
334. 递增的三元子序列

给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列。
如果存在这样的三元组下标 (i, j, k) 且满足 i < j < k ，使得 nums[i] < nums[j] < nums[k] ，返回 true ；否则，返回 false 。

思路：用一个数组维护当前所有已找到的、长度为 $i + 1$ 的递增子序列中，末尾元素的最小值。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool increasingTriplet(vector<int>& nums){
    vector<int> g;
    // 第一个元素进入时，g空，必然找不到大于x的数，g[0]=x
    // g[0]==x表示长度为1的递增子序列的最小末尾为x
    // 后续元素进行比较，当前元素与g中的所有数
    // 如果大于所有数，说明可以延长，同时push_back
    // 如果没有大于所有数，不延长，但是更新对应的末尾元素
    for(int x : nums){
        auto it = lower_bound(g.begin(), g.end(), x);
        if(it - g.begin() == 2) return true;
        if(it == g.end()) g.push_back(x);
        else *it = x;
    }
    return false;
}

int main(){
    vector<int> nums = {2, 1, 5, 0, 4, 6};
    cout << boolalpha << increasingTriplet(nums) << "\n";
    return 0;
}