/*
18. 四数之和

给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> ans;
    for(int i = 0; i < n - 3; i++) {
        if(i > 0 && nums[i] == nums[i - 1]) continue;
        long long s = 0LL + nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3];
        if(s > target) break;
        s = 0LL + nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1];
        if(s < target) continue;
        for(int j = i + 1; j < n - 2; j++) {
            if(j > i + 1 && nums[j] == nums[j - 1]) continue;
            s = 0LL + nums[i] + nums[j] + nums[j + 1] + nums[j + 2];
            if(s > target) break;
            s = 0LL + nums[i] + nums[j] + nums[n - 2] + nums[n - 1];
            if(s < target) continue;
            int k = j + 1, l = n - 1;
            while(k < l) {
                s = 0LL + nums[i] + nums[j] + nums[k] + nums[l];
                if(s == target){
                    ans.push_back({nums[i], nums[j], nums[k], nums[l]});
                    for(k++; k < l && nums[k] == nums[k - 1]; k++);
                    for(l--; k < l && nums[l] == nums[l + 1]; l--);
                }
                else if(s > target) l--;
                else k++;
            }
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {1, 0, 0, -2, 2, -1};
    vector<vector<int>> ans = fourSum(nums, 0);
    for(auto& it : ans) {
        for(int num : it) cout << num << " ";
        cout << "\n";
    }
    return 0;
}