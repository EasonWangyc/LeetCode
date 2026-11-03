/*
452. 用最少数量的箭引爆气球

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
*/
#include <bits/stdc++.h>
using namespace std;

bool hasIntersection(vector<int>& a, vector<int>& b) {
    if(a[1] >= b[0]) return true;
    return false;
}

int findMinArrowShots(vector<vector<int>>& points) {
    sort(points.begin(), points.end());
    vector<int> ref = points[0];
    int n = points.size();
    int count = 1;
    for(int i = 1; i < n; i++) {
        if(hasIntersection(ref, points[i])) {
            ref = {max(ref[0], points[i][0]), min(ref[1], points[i][1])};
        }
        else {
            count++;
            ref = points[i];
        }
    }
    return count;
}

// 优化：实际上只需要维护一个右端点即可

int main() {
    vector<vector<int>> points = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    cout << findMinArrowShots(points) << "\n";
    return 0;
}