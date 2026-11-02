/*
216. 组合总和Ⅲ

找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
- 只使用数字1到9
- 每个数字 最多使用一次 

返回 所有可能的有效组合的列表 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。
*/
#include <bits/stdc++.h>
using namespace std;

class solution {
private:
    vector<vector<int>> ans;
    vector<int> path;
    // i为当前最大候选数，left_sum为剩余和
    void dfs(int i, int left_sum, int k) {
        int d = k - path.size();
        // 剪枝1：如果剩余sum小于0或者大于剩下元素之和，说明找不到，直接返回
        // i + (i-1) + ... + (i-d+1) = (2i-d+1)*d/2
        if(left_sum < 0 || left_sum > (2 * i - d + 1) * d / 2) return;
        if(d == 0) {
            ans.push_back(path);
            return;
        }
        // 剪枝2：还剩d个数要挑，当前数必须大于等于d，否则不够
        for(int j = i; j >= d; j--) {
            path.push_back(j);
            // 已经挑选j，所以下一个为j-1
            dfs(j - 1, left_sum - j, k);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationsSum3(int k, int n) {
        ans.clear();
        path.clear();
        dfs(9, n, k);
        return ans;
    }
};

int main() {
    solution s;
    vector<vector<int>> ans = s.combinationsSum3(3, 9);
    for(auto& v : ans){
        for(int num : v) cout << num << " ";
        cout << "\n";
    }
    return 0;
}