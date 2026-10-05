/*
287. 寻找重复数

给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。
假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

思路：由于题目给出数组长度为n+1，数组中所有数字都在[1,n]之间，将下标看成链表节点的地址，把其中存储的值nums[i]看作指针i->nums[i]，重复数字的本质是数组中有i和j满足nums[i]=nums[j]，即i和j都指向同一个下标，相当于链表有环。
*/
#include <vector>
#include <iostream>
using namespace std;

int findDuplicate(vector<int>& nums){
    int slow = 0, fast = 0;
    while(true){
        slow = nums[slow];      // 相当于slow = slow->next
        fast = nums[nums[fast]];// 相当于fast = fast->next->next 
        if(slow == fast) break;
    }
    fast = 0;
    while(slow != fast){
        // 由环形链表Ⅱ可知，当fast回到起点两者同步运动时，必定相遇在环处
        slow = nums[slow];
        fast = nums[fast];
    }
    // 不需要返回nums[slow]，这样相当于返回node->next了
    return slow;
}

int main(){
    vector<int> nums = {1, 3, 4, 2, 2};
    cout << findDuplicate(nums) << "\n";
    return 0;
}