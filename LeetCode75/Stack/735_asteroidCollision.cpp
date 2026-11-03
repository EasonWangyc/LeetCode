/*
735. 小行星碰撞

给定一个整数数组 asteroids，表示在同一行的小行星。数组中小行星的索引表示它们在空间中的相对位置。

对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。每一颗小行星以相同的速度移动。

找出碰撞后剩下的所有小行星。碰撞规则：两个小行星相互碰撞，较小的小行星会爆炸。如果两颗小行星大小相同，则两颗小行星都会爆炸。两颗移动方向相同的小行星，永远不会发生碰撞。
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
    vector<int> ans;
    for(int aster : asteroids) {
        bool alive = true;  // 当前行星是否存活，正值直接push
        while(aster < 0 && alive && !ans.empty() && ans.back() > 0) {
            if(ans.back() < -aster) ans.pop_back();
            else if(ans.back() == -aster) {
                ans.pop_back();
                alive = false;
            }else alive = false;
        }
        if(alive) ans.push_back(aster);
    }
    return ans;
}

int main() {
    vector<int> asteroids = {5, 10, -5};
    vector<int> ans = asteroidCollision(asteroids);
    for(int num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}