/*
1385. 两个数组间的距离值

给你两个整数数组 arr1 ， arr2 和一个整数 d ，请你返回两个数组之间的 距离值 。

「距离值」 定义为符合此距离要求的元素数目：对于元素 arr1[i] ，不存在任何元素 arr2[j] 满足 |arr1[i]-arr2[j]| <= d 。
*/
#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& nums, int target){
    int l = 0, r = nums.size();
    // 左闭右开区间
    while(l < r){
        int mid = l + (r - l) / 2;
        if(target <= nums[mid]) r = mid;
        else l = mid + 1;
    }
    return l;
}

int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d){
    sort(arr2.begin(), arr2.end());
    int ans = 0;
    for(int num : arr1){
        int pos = find(arr2, num);
        bool flag = true;
        if(pos < arr2.size() && abs((long long)num - arr2[pos]) <= d) flag = false;
        if(pos > 0 && abs((long long)num - arr2[pos - 1]) <= d) flag = false;
        if(flag) ans++;
    }
    return ans;
}