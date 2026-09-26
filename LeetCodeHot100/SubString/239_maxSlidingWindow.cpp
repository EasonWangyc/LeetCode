/*
239. 滑动窗口最大值

给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值 。

思路：双端队列
*/
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k){
    int n = nums.size();
    vector<int> ans(n - k + 1);
    // 保存下标，保证队首元素对应的nums[i]值大于队尾元素对应的值
    deque<int> q;
    for(int i = 0; i < n; i++){
        // 如果队尾旧元素 nums[q.back()] <= nums[i]，那么这些队尾旧元素永远不可能再成为任何后续窗口的最大值。
        while(!q.empty() && nums[q.back()] <= nums[i]) q.pop_back();
        q.push_back(i);
        int l = i - k + 1;
        if(q.front() < l) q.pop_front();
        if(l >= 0) ans[l] = nums[q.front()];
    }
    return ans;
}

int main(){
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> ans = maxSlidingWindow(nums, 3);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}