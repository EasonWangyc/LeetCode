/*
2462. 雇佣 K 位工人的总代价

给你一个下标从 0 开始的整数数组 costs ，其中 costs[i] 是雇佣第 i 位工人的代价。

同时给你两个整数 k 和 candidates 。我们想根据以下规则恰好雇佣 k 位工人：

总共进行 k 轮雇佣，且每一轮恰好雇佣一位工人。
在每一轮雇佣中，从最前面 candidates 和最后面 candidates 人中选出代价最小的一位工人，如果有多位代价相同且最小的工人，选择下标更小的一位工人。
比方说，costs = [3,2,7,7,1,2] 且 candidates = 2 ，第一轮雇佣中，我们选择第 4 位工人，因为他的代价最小 [3,2,7,7,1,2] 。
第二轮雇佣，我们选择第 1 位工人，因为他们的代价与第 4 位工人一样都是最小代价，而且下标更小，[3,2,7,7,2] 。注意每一轮雇佣后，剩余工人的下标可能会发生变化。
如果剩余员工数目不足 candidates 人，那么下一轮雇佣他们中代价最小的一人，如果有多位代价相同且最小的工人，选择下标更小的一位工人。
一位工人只能被选择一次。
返回雇佣恰好 k 位工人的总代价。
*/
#include <bits/stdc++.h>
#include <algorithm>
#include <numeric>
using namespace std;

long long totalCost(vector<int>& costs, int k, int candidates) {
    int n = costs.size();
    // 直接选取整个数组中的k个最小值
    if(candidates * 2 + k > n){
        nth_element(costs.begin(), costs.begin() + k, costs.end());
        return accumulate(costs.begin(), costs.begin() + k, 0LL);
    }
    priority_queue<int, vector<int>, greater<>> pre, suf;
    for(int i = 0; i < candidates; i++){
        pre.push(costs[i]);
        suf.push(costs[n - 1 - i]);
    }
    long long ans = 0;
    int i = candidates, j = n - 1 - candidates;
    while(k--){
        if(pre.top() <= suf.top()){
            ans += pre.top();
            pre.pop();
            pre.push(costs[i++]);
        } else {
            ans += suf.top();
            suf.pop();
            suf.push(costs[j--]);
        }
    }
    return ans;
}

int main() {
    vector<int> costs = {17, 12, 10, 2, 7, 2, 11, 20, 8};
    int k = 3, candidates = 4;
    cout << totalCost(costs, k, candidates) << "\n";
    return 0;
}