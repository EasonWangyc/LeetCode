/*
1732. 找到最高海拔

有一个自行车手打算进行一场公路骑行，这条路线总共由 n + 1 个不同海拔的点组成。自行车手从海拔为 0 的点 0 开始骑行。

给你一个长度为 n 的整数数组 gain ，其中 gain[i] 是点 i 和点 i + 1 的 净海拔高度差（0 <= i < n）。请你返回 最高点的海拔 。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int largestaAltitude(vector<int>& gain){
    int max_altitude = 0;
    int cur = 0;
    for(int x : gain)
    {
        cur += x;
        max_altitude = max(max_altitude, cur);
    }
    return max_altitude;
}

int main(){
    vector<int> gain = {-5, 1, 5, 0, -7};
    cout << largestaAltitude(gain) << "\n";
    return 0;
}