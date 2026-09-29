/*
1679. K 和数对的最大数目

给你一个整数数组 nums 和一个整数 k 。

每一步操作中，你需要从数组中选出和为 k 的两个整数，并将它们移出数组。

返回你可以对数组执行的最大操作数。
*/
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

int maxOperations(vector<int>& nums, int k){
    unordered_map<int, int> cnt;
    int ans = 0;
    for(int x : nums){
        if(cnt[k - x] > 0){ // 3 + 3 = 6这种情况
            ans++;
            cnt[k - x]--;
        }else cnt[x]++;
    }
    return ans;
}

int main(){
    vector<int> nums = {1, 2, 3, 4};
    cout << maxOperations(nums, 5) << "\n";
    return 0;
}