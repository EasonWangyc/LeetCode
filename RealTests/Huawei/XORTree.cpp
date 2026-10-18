/*
老师为孩子们设计了一个使用异或树的游戏。游戏在一棵有n个节点的树上进行，节点编号从1到n，树的根节点是节点1，各节点之间的父子关系可从根节点1开始基于连边关系进行推导。
每个节点i有一个初始值$init_i$，其值要么是0，要么是1。
在游戏过程中，可以对树执行若干次(可能为0次)操作，具体操作就是选择某个节点$x$。
在选中节点$x$之后，节点$x$的值会产生翻转(从0变成1或者从1变成0):
$x$的子节点值则保持不变，$x$的孙子节点的值也会翻转，$x$的曾孙节点的值保持不变，依次逐代类推(即距离某节点为奇数的子节点保持值不变，距离偶数的子节点会跟随翻转)。
游戏的最终目标是使得每个节点$i$的值都变为输入的目标值$goal_i$，$goal_i$也只能是0或1。你需要使用最少的操作次数来达成游戏目标。

输入描述：

第一行包含一个整数n($1 \le n \le 10^5$)，代表树存在n个节点。
接下来的n-1行，每行包含两个整数ui和vi($1 \le ui,vi \le n; ui \ne vi$)，表示树节点ui和vi之间有树干连接。
下一行包含n个整数，第i个数字对应于树节点的值$init_i$（$init_i$只能是0或1）。
接下来一行也包含n个整数，第i个数字对应于树节点目标值$goal_i$（$goal_i$只能是0或1）。
特殊说明:所有树节点之间的连接都是合法有效的，所有输入数据都能保证能构成一棵树。

输出描述：
输出一个整数，代表最少的操作次数。

思路：
由无向图构建树结构；异或的性质：`1^1=0, 0^1=1, 1^0=1, 0^0=0`，。
*/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int solution(vector<vector<int>>& adj, vector<int>& init, vector<int>& goal, int n){
    // BFS 计算深度和父节点
    vector<int> parent(n + 1, 0);
    vector<int> depth(n + 1, 0);
    queue<int> q;
    q.push(1);      // 根节点入队
    parent[1] = -1; // 根节点的父节点设为-1表示没有父节点
    depth[1] = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : adj[u]){
            if(v == parent[u]) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }

    int ans = 0;
    struct State{int node, even, odd;};
    stack<State> st;
    st.push({1, 0, 0});
    while(!st.empty()){
        State cur = st.top();
        st.pop();
        int u = cur.node, even = cur.even, odd = cur.odd;
        int flip = (depth[u] % 2 == 0) ? even : odd;
        int delta = goal[u] ^ init[u];
        if(flip != delta){
            ans++;
            if(depth[u] % 2 == 0) even ^= 1;
            else odd ^= 1;
        }
        for(int v : adj[u]){
            if(v == parent[u]) continue;
            st.push({v, even, odd});
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> init(n + 1);
    vector<int> goal(n + 1);
    for(int i = 1; i <= n; i++) cin >> init[i];
    for(int i = 1; i <= n; i++) cin >> goal[i];
    int ans = solution(adj, init, goal, n);
    cout << ans << "\n";
    return 0;
}