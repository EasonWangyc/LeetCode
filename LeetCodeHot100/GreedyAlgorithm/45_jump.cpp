/*
45. 跳跃游戏Ⅱ

给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。
每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：0 <= j <= nums[i] 且 i + j < n
返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int jump(vector<int>& nums){
    int n = nums.size();
    int ans = 0;
    // cur表示第ans步能够到达的最远位置，next表示当前能够覆盖的所有格子里起跳能到达的最远位置
    int cur = 0, next = 0;
    // for 循环是在巡视当前这一步能够落脚的所有可能性，而不是真的在每一步都跳一下
    // 循环只到n-1，因为题目写明必定可以跳到，且n-2或之前已经ans++，n-1时是不需要跳跃的，但是可能会出现该次循环中i==cur导致ans++的情况
    for(int i = 0; i < n - 1; i++){
        next = max(next, nums[i] + i);
        if(i == cur){
            cur = next;
            ans++;
        }
    }
    return ans;
}

int main(){
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << jump(nums) << "\n";
    return 0;
}