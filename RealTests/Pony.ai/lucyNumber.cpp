/*
Popo把n个玩具排成一排，它对第i个玩具的喜爱度为a_i。
Popo的幸运数字是k，它想知道有多少个区间的和是k的非负整数次幂

n<=1e^3或n<=1e^5
abs(k)<=10
abs(a_i)<=1e^9

输入：
4 2
2 2 2 2

输出：
8
*/
#include <bits/stdc++.h>
using namespace std;

const long long MAX_SUM = 1e14;

long long lucyNumber(vector<long long>& nums, vector<long long>& targets){
    unordered_map<long long, int> mp;
    mp[0] = 1; // 处理[0, r]的情况
    int n = nums.size();
    long long pre = 0;
    long long ans = 0;
    for(int i = 0; i < n; i++){
        pre += nums[i];
        for(long long target : targets){
            long long need = pre - target;
            auto it = mp.find(need);
            if(it != mp.end()) ans += it->second;
        }
        mp[pre]++;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<long long> targets;
    if(k == 1) targets.push_back(1);
    else if(k == - 1){
        targets.push_back(1);
        targets.push_back(-1);
    }else if(k == 0) targets.push_back(0);
    else{
        long long cur = 1;
        while(abs(cur) <= MAX_SUM){
            targets.push_back(cur);
            cur *= k;
        }
    }
    cout << lucyNumber(a, targets) << "\n";
    return 0;
}