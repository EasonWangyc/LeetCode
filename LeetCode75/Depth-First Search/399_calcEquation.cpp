/*
399. 除法求值

给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。
另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果；未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。
*/
#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<int> fa;
    vector<double> mul;
    UnionFind(int n) : fa(n), mul(n, 1) {
        iota(fa.begin(), fa.end(), 0);      // 构建初始集合{0}、{1}、...、{n - 1}
    }
    int find(int x){
        if(fa[x] != x){
            int root = find(fa[x]);
            mul[x] *= mul[fa[x]];
            fa[x] = root;
        }
        return fa[x];
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
    //    x --------- y
    //   /           /
    // from ------- to
    // 已知 x/from = mul[from] 和 y/to = mul[to]，现在合并 from 和 to，新增信息 to/from = value
    // 由于 y/from = (y/x) * (x/from) = (y/to) * (to/from)
    // 所以 y/x = (y/to) * (to/from) / (x/from) = mul[to] * value / mul[from]
    void merge(int from, int to, double value){
        int x = find(from), y = find(to);
        if(x == y) return;
        mul[x] = mul[to] * value / mul[from];
        fa[x] = y;
    }
};

vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
    unordered_map<string, int> variable_to_id;
    for(auto& equation : equations){
        for(auto& s : equation){
            if(!variable_to_id.count(s)) variable_to_id[s] = variable_to_id.size(); 
        }
    }
    int n = variable_to_id.size();
    UnionFind uf(n);
    for(int i = 0; i < (int)equations.size(); i++){
        uf.merge(variable_to_id[equations[i][1]], variable_to_id[equations[i][0]], values[i]);
    }
    vector<double> ans;
    for(auto& query : queries){
        auto it_c = variable_to_id.find(query[0]);
        if(it_c == variable_to_id.end()){
            ans.push_back(-1);
            continue;
        }
        auto it_d = variable_to_id.find(query[1]);
        if(it_d == variable_to_id.end(0) || !uf.same(it_c->second, it_d->second)){  // query不存在或者不在同一个并查集中
            ans.push_back(-1);
            continue;
        }
        ans.push_back(uf.mul[it_d->second] / uf.mul[it_c->second]);
    }
    return ans;
}

int main(){
    vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}, {"d", "e"}};
    vector<double> values = {2.0, 3.0, 4.0};
    vector<vector<string>> queries = {{"a", "c"}, {"b, d"}, {"x", "x"}};
    vector<double> ans = calcEquation(equations, values, queries);
    cout << fixed << setprecision(5);
    for(auto& num : ans) cout << num << " ";
    cout << "\n";
    return 0;
}