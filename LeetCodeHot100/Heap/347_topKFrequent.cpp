/*
347. 前 K 个高频元素

给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
*/
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k){
    unordered_map<int, int> cnt;
    int max_cnt = 0;
    for(int x : nums){
        cnt[x]++;
        max_cnt = max(max_cnt, cnt[x]);
    }
    vector<vector<int>> bucket(max_cnt + 1);
    for(auto& [x, c] : cnt) bucket[c].push_back(x);
    vector<int> ans;
    for(int i = max_cnt; k > ans.size(); i--) ans.insert(ans.end(), bucket[i].begin(), bucket[i].end());
    return ans;
}

int main(){
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    vector<int> ans = topKFrequent(nums, 2);
    for(int x : ans) cout << x << "\n";
    return 0;
}