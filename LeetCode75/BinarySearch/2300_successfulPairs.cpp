/*
2300. 咒语和药水的成功对数

给你两个正整数数组 spells 和 potions ，长度分别为 n 和 m ，其中 spells[i] 表示第 i 个咒语的能量强度，potions[j] 表示第 j 瓶药水的能量强度。

同时给你一个整数 success 。一个咒语和药水的能量强度 相乘 如果 大于等于 success ，那么它们视为一对 成功 的组合。

请你返回一个长度为 n 的整数数组 pairs，其中 pairs[i] 是能跟第 i 个咒语成功组合的 药水 数目。
*/
#include <bits/stdc++.h>
using namespace std;

// 实际上直接使用lower_bound()即可

// 找到数组中第一个大于等于k的元素的下标
int find(vector<int>& potions, long long k) {
    int l = 0, r = potions.size() - 1;
    while(l <= r){
        int mid = l + (r - l) / 2;
        if(potions[mid] >= k) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

vector<int> successPairs(vector<int>& spells, vector<int>& potions, long long success) {
    sort(potions.begin(), potions.end());
    vector<int> ans;
    int n = potions.size();
    for(int num : spells){
        long long target = success % num == 0 ? success / num : success / num + 1;
        // 或：long long target = (success + num - 1) / num;
        ans.push_back(n - find(potions, target));
    }
    return ans;
}

int main(){
    vector<int> spells = {3, 1, 2};
    vector<int> potions = {8, 5, 8};
    long long success = 16;
    vector<int> ans = successPairs(spells, potions, success);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}