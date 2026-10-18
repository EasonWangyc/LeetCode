#include <iostream>
#include <vector>

using namespace std;

int ans = 0;
vector<vector<int>> adj;
vector<int> init_val, goal_val;

// u: 当前节点, p: 父节点 (避免走回头路)
// depth: 当前深度 (根节点深度为 0)
// even_flip: 偶数层祖先累计的翻转次数奇偶性 (0 或 1)
// odd_flip:  奇数层祖先累计的翻转次数奇偶性 (0 或 1)
void dfs(int u, int p, int depth, int even_flip, int odd_flip) {
    // 决定当前节点受哪一类翻转影响
    int cur_flip = (depth % 2 == 0) ? even_flip : odd_flip;
    
    // 当前节点的实际当前值 = 初始值 ^ 上层传递下来的翻转影响
    int current_val = init_val[u] ^ cur_flip;
    
    // 如果当前值与目标值不符，必须在此处操作翻转一次
    if (current_val != goal_val[u]) {
        ans++;
        // 翻转当前深度的标记，并传递给后代
        if (depth % 2 == 0) {
            even_flip ^= 1;
        } else {
            odd_flip ^= 1;
        }
    }
    
    // 递归遍历所有邻居节点
    for (int v : adj[u]) {
        if (v == p) continue; // 不往回走
        dfs(v, u, depth + 1, even_flip, odd_flip);
    }
}

int main() {
    // 快速 I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 统一下标为 1-based，防止越界和错位
    init_val.resize(n + 1);
    goal_val.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> init_val[i];
    for (int i = 1; i <= n; i++) cin >> goal_val[i];

    // 从根节点 1 出发，深度为 0，初始翻转均为 0
    dfs(1, 0, 0, 0, 0);

    cout << ans << "\n";

    return 0;
}