/*
POPO的robotaxi运营范围覆盖了n个站点，这n个站点分别被标为1到n，它们被n-1条无向边联通，这些边的长度均为正。
站点a到站点b的trip可以表示为站点的序列且序列中的站点各不相同，即(a，....，b)，trip的长度为序列经过的边的和。
POPO想知道两趟完全不相交的trip(即序列无公共站点)的长度之积的最大值。

输入格式：
第一行n(n<=200)，为站点数量，接下来n-1行，每行为无向边的端点a，b和长度。
输出格式：
一个正整数，为最大值。

示例输入：
6
1 2 1
2 3 1
2 4 1
5 4 1
6 4 1

示例输出：
4
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int to;         // 指向
    long long w;    // 边的权值
    int id;         // 边的id
};

vector<vector<Edge>> adj;

long long getDiameter(int u, int p, int blocked_edge_id, long long& max_d){
    long long first = 0, second = 0; // 多叉树情况下，一条简单路径必定是由两条单链组成的，这里保存两个最大的单链长度
    for(const auto& edge : adj[u]){
        int v = edge.to;
        if(v == p || edge.id == blocked_edge_id) continue;
        long long cur = getDiameter(v, u, blocked_edge_id, max_d) + edge.w;
        if(cur > first){
            second = first;
            first = cur;
        }else if(cur > second) second = cur;
    }
    max_d = max(max_d, first + second);
    return first;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    adj.resize(n + 1);
    struct RawEdges{
        int u, v;
        long long w;
    };
    vector<RawEdges> edges;
    // 建图
    for(int i = 0; i < n - 1; i++){
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w, i});
        adj[v].push_back({u, w, i});
        edges.push_back({u, v, w});
    }
    long long max_product = 0;
    for(int i = 0; i < n - 1; i++){
        int u = edges[i].u;
        int v = edges[i].v;
        // 断开第i条边
        long long d_u = 0, d_v = 0;
        getDiameter(u, 0, i, d_u);
        getDiameter(v, 0, i, d_v);
        max_product = max(max_product, d_u * d_v);
    }
    cout << max_product << "\n";
    return 0;
}