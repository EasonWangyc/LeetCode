/*
小明在玩一个数字消除游戏。游戏开始时，屏幕上有一排n个互不相同的数字。
游戏中有两种技能：
山谷消除:消除所有"山谷"位置的数字。一个数字处于"山谷"位置，当且仅当它比左右相邻的数字都小。
山峰消除:消除所有"山峰"位置的数字。一个数字处于"山峰"位置，当且仅当它比左右相邻的数字都大。
注意，最左边和最右边的数字没有两侧邻居，因此永远不会被消除。每次使用技能时，所有符合条件的数字同时消除，消除后剩余数字保持原有的相对顺序紧凑排列。
小明将依次使用m次技能，请你输出每次使用技能后屏幕上剩余的数字个数。

输入描述：
第一行一个正整数T，表示测试数据组数对于每组测试数据第一行两个正整数n,m，分别表示初始数字个数和技能使用次数。
第二行n个正整数a1，a2，...，an，表示初始数字序列，保证互不相同。
第三行m个正整数t1，t2，...，tm，其中ti=1表示使用山谷消除，ti=2表示使用山峰消除。
1≤T≤5，1≤n,m≤200000,1≤ai≤10^9，所有ai互不相同，ti属于(1,2)。

输出描述：
对于每组测试数据，输出m行，第i行一个整数表示第i次使用技能后剩余的数字个数。

示例：
输入：
1
6 4
3 5 1 4 2 6
2 1 2 1

输出：
4
3
3
2
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// 判断 x 当前是否是山谷
bool isValley(int x, const vector<long long>& a, const vector<int>& L, const vector<int>& R) {
    // 当前序列的左右端点不能被删除
    if (L[x] == 0 || R[x] == 0) return false;
    return a[x] < a[L[x]] && a[x] < a[R[x]];
}

// 判断 x 当前是否是山峰
bool isPeak(int x, const vector<long long>& a, const vector<int>& L, const vector<int>& R) {
    // 当前序列的左右端点不能被删除
    if (L[x] == 0 || R[x] == 0) return false;
    return a[x] > a[L[x]] && a[x] > a[R[x]];
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(n + 1);
    vector<int> ops(m);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> ops[i];
    }

    // L[i]：当前 i 左边最近的存活节点
    // R[i]：当前 i 右边最近的存活节点
    vector<int> L(n + 1), R(n + 1);

    for (int i = 1; i <= n; i++) {
        L[i] = i - 1;
        R[i] = i + 1;
    }

    if (n >= 1) {
        L[1] = 0;
        R[n] = 0;
    }

    // 当前所有山谷、山峰
    set<int> valleys;
    set<int> peaks;

    // 初始化山谷和山峰
    for (int i = 2; i < n; i++) {
        if (isValley(i, a, L, R)) {
            valleys.insert(i);
        } else if (isPeak(i, a, L, R)) {
            peaks.insert(i);
        }
    }

    int cnt = n;

    for (int op : ops) {

        // 本轮需要同时删除的所有节点
        vector<int> toRemove;

        if (op == 1) {
            // 删除所有山谷
            toRemove.assign(valleys.begin(), valleys.end());
        } else {
            // 删除所有山峰
            toRemove.assign(peaks.begin(), peaks.end());
        }

        // 如果这一轮没有可以删除的节点
        if (toRemove.empty()) {
            cout << cnt << '\n';
            continue;
        }

        cnt -= (int)toRemove.size();

        /*
         * affected：
         * 删除节点后，只有它们左右相邻的节点
         * 可能改变“山峰/山谷”状态。
         */
        vector<int> affected;

        // 先把所有即将删除的节点从集合中移除
        for (int x : toRemove) {
            valleys.erase(x);
            peaks.erase(x);
        }

        /*
         * 开始真正删除。
         *
         * 注意：
         * 同一轮被删除的都是山峰，或者都是山谷。
         * 两个山峰不可能相邻，两个山谷也不可能相邻。
         *
         * 所以可以逐个更新双向链表。
         */
        for (int x : toRemove) {
            int l = L[x];
            int r = R[x];

            if (l != 0) {
                affected.push_back(l);
            }

            if (r != 0) {
                affected.push_back(r);
            }

            // 将 x 从链表中删除
            if (l != 0) {
                R[l] = r;
            }

            if (r != 0) {
                L[r] = l;
            }
        }

        // 同一个节点可能同时受到多个删除节点影响
        sort(affected.begin(), affected.end());
        affected.erase(
            unique(affected.begin(), affected.end()),
            affected.end()
        );

        /*
         * 重新判断受影响节点的状态
         */
        for (int x : affected) {

            // 先删除旧状态
            valleys.erase(x);
            peaks.erase(x);

            // 然后根据新的左右邻居重新判断
            if (isValley(x, a, L, R)) {
                valleys.insert(x);
            } else if (isPeak(x, a, L, R)) {
                peaks.insert(x);
            }
        }

        cout << cnt << '\n';
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}