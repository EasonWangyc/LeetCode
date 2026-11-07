/*
16. 最接近的三数之和

给定一个长度为 n 的整数数组 nums 和 一个整数 target。

请你从 nums 中选出三个在 不同下标位置 的整数，使它们的和与 target 最接近。

返回这三个数的和。

假定每组输入只存在 恰好 一个解。
*/
#include <bits/stdc++.h>
using namespace std;

int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int ans = INT_MAX / 2;
    for(int i = 0; i < n - 2; i++) {
        if(i > 0 && nums[i] == nums[i - 1]) continue;
        int s = nums[i] + nums[i + 1] + nums[i + 2];
        if(s > target) {
            if(s - target < abs(ans - target)) ans = s;
            break;
        }
        s = nums[i] + nums[n - 2] + nums[n - 1];
        if(s < target) {
            if(target - s < abs(ans - target)) ans = s;
            continue;
        }
        int j = i + 1, k = n - 1;
        while(j < k) {
            s = nums[i] + nums[j] + nums[k];
            if(s == target) return target;
            if(abs(s - target) < abs(ans - target)) ans = s;
            if(s > target) k--;
            if(s < target) j++;
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {0, 0, 0};
    cout << threeSumClosest(nums, 1) << "\n";
    return 0;
}