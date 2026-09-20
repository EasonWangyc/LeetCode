/*
有一段按顺序进行的注水流程，共有n次注水，第i次注水量为非负整数vi
给定q个容量C1,C2,...,Cq
设前缀和p=Σvk(k=1到i)，则每次注水后的水位为Li(C)=min(C,pi)。
定义总累积水位S(C)=ΣLi(C)=Σ(min(C,pi))
对于j，请分别计算对应的S(Cj)

输入描述：
每个测试文件包含多组测试数据。第一行输入一个整数T(1≤T≤10^5)表示数据组数，每组测试数据描述如下:
第一行输入两个整数n,q(1≤n≤2x10^5,1≤q≤2x10^5)。
第二行输入n个整数vi(0≤vi≤10^6)
第三行输入q个整数Ci(0≤Ci≤10^12)

输出描述：
对每组数组输出q个Sj，以空格分隔。

注意：如果使用暴力循环部分会超时(25%)，应该使用二分查找+前缀和。
前缀和天然具有单调性，对于任意一个C，都可以利用std:upper_bound找到分割点，然后直接公式计算不需要循环
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, q;
    if (!(cin >> n >> q)) return;

    vector<long long> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // 1. 计算一级前缀和 p_i (水位)
    vector<long long> p(n);
    p[0] = v[0];
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1] + v[i];
    }

    // 2. 计算二级前缀和 pref_sum，用于 O(1) 求 p 数组的前缀和
    // pref_sum[k] 表示 p[0] + p[1] + ... + p[k-1]
    vector<long long> pref_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref_sum[i + 1] = pref_sum[i] + p[i];
    }

    // 3. 处理每个容量查询 C_j
    for (int j = 0; j < q; j++) {
        long long C;
        cin >> C;

        // 二分查找第一个大于 C 的位置
        // cnt 表示小于等于 C 的元素个数
        int cnt = upper_bound(p.begin(), p.end(), C) - p.begin();

        // 答案 = (前 cnt 个原本的 p 之和) + (剩下的 n - cnt 个全被截断为 C)
        long long ans = pref_sum[cnt] + (long long)(n - cnt) * C;

        cout << ans << (j + 1 == q ? "" : " ");
    }
    cout << "\n";
}

int main() {
    // 极其重要的 I/O 提速，防止大数据下由于 cin/cout 变慢
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}