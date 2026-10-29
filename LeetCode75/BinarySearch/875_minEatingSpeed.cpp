/*
875. 爱吃香蕉的珂珂

珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 h 小时后回来。

珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  

珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。

返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
*/
#include <bits/stdc++.h>
using namespace std;

int minEatingSpeed(vector<int>& piles, int h) {
    int l = 1;
    int r = *max_element(piles.begin(), piles.end());
    while(l <= r){
        int mid = l + (r - l) / 2;
        long long total_hour = 0;
        for(int p : piles) total_hour += (p + mid - 1LL) / mid;
        if(total_hour <= h) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

int main() {
    vector<int> piles = {3, 6, 7, 11};
    cout << minEatingSpeed(piles, 8) << "\n";
    return 0;
}