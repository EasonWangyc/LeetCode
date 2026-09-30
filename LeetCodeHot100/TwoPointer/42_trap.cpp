/*
42. 接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int trap(vector<int>& height) {
    int ans = 0;
    int l = 0, r = height.size() - 1;
    int pre_max = 0, suf_max = 0;
    while(l < r){
        pre_max = max(pre_max, height[l]);
        suf_max = max(suf_max, height[r]);
        if(pre_max < suf_max){
            ans += pre_max - height[l];
            l++;
        }else{
            ans += suf_max - height[r];
            r--;
        }
    }
    return ans;
}

int main(){
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    int ans = trap(height);
    cout << ans << "\n";
    return 0;
}