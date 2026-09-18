/*
小沃有一个长度为n的数组a，其中第i个数为ai。
有人对该数组进行了一次“加密”操作:
他选择两个不同下标i,j(1≤i,j≤n,i≠j)，将ai,aj从数组中取出并向数组中插入一个新数ai+aj，其余元素保持原有相对顺序不变。
操作后数组长度变为n-1。
你只知道加密后数组所有元素的乘积对10^9+7取模的值，即：
$$P \equiv \prod_{x \in b} x \quad\left(\bmod 10^{9}+7\right)$$
其中b表示加密后的数组。
请你找出一组可能的下标(i,j)(满足1≤i,j≤n,i≠j)，使得存在上述一次加密操作后得到的数组乘积模值等于给定的P。
若有多组答案，输出任意一组;若不存在，输出-1。
输入描述
每个测试文件均包含多组测试数据。第一行输入一个整数T(1≤T≤2x10^5)表示数据组数，每组测试数据描述如下:
第一行输入一个整数n(2≤n≤2x105)。
第二行输入n个整数a1,a2,...,an (0≤ai≤10^9)。
第三行输入一个整数P(0≤P<10^9+7)，表示加密后数组乘积对10^9+7取模的值。
除此之外，保证单个测试文件中所有测试数据的n之和不超过5x10^5。

分类讨论数据中0的个数count：
1. count>=3：无论怎么选i和j，剩余树中还有0，此时乘积恒为0，对P进行讨论
2. count=2：若选了两个0，此时ai+aj=0，乘积还是0；若选了小于等于1个0，乘积还是0，对P进行讨论
3. count=1：设唯一的0所在下标为z，所有非零元素乘积为Q
- 选取了唯一的0，此时剩余乘积恰好为Q，对P进行讨论
- 未选到0，新乘积恒为0，对P进行讨论，如果P=0：若n>=3，只要在非零数中任选两个下标即可；若n=2，此时回退到上面一种情况
4. count=0：此时数据全为整数
- P=0，选取的两个必须满足相加恰好等于10^9+7
- p!=0，转换为在模的意义下找两数之和（用到了费马小定理和快速幂乘法）
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long MOD = 1e9 + 7;

long long quickpower(long long a, long long b){
    long long res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = (res * a) % MOD; // 判断b的最后一位
        a = (a * a) % MOD;
        b >>= 1; // b右移一位，相当于除2
    }
    return res;
}

long long inv(long long n){
    return quickpower(n, MOD - 2);  // 费马小定理，在模的意义下求一个数的倒数
}

void solve(){
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    vector<int> zeros;
    for(int i = 1; i <=n; i++){
        cin >> a[i];
        if(a[i] == 0) zeros.push_back(i);
    }
    long long P;
    cin >> P;
    int cnt0 = zeros.size();

    // 1. 至少两个0，乘积必定为0
    if(cnt0 >= 2){
        if(P == 0) cout << "1 2\n";
        else cout << "-1\n";
        return;
    }

    // 2.一个0
    if(cnt0 == 1){
        int z = zeros[0];
        long long Q = 1;
        for(int i = 1; i <= n; i++){
            if(i != z) Q = (Q * (a[i] % MOD)) % MOD;
        }
        if(P == Q){
            int other = (z == 1 ? 2 : 1);
            cout << z << " " << other << "\n";
            return;
        }
        if(P == 0 && n >= 3){
            vector<int> others;
            for(int i = 1; i <= n; i++){
                if(i != z) others.push_back(i);
                if(others.size() == 2) break;   // 找到任意两个非0位置即可
            }
            cout << others[0] << " " << others[1] << "\n";
            return;
        }
        cout << "-1\n";
        return;
    }

    // 3.没有0的情况且P==0（寻找 a_i + a_j = MOD）
    if(P == 0){
        vector<pair<long long, int>> sorted_a(n);
        for(int i = 1; i <= n; i++){
            sorted_a[i - 1] = {a[i], i};
        }
        sort(sorted_a.begin(), sorted_a.end());
        // 二分查找
        int l = 0, r = n - 1;
        while(l < r){
            long long sum = sorted_a[l].first + sorted_a[r].first;
            if(sum == MOD){
                cout << sorted_a[l].second << " " << sorted_a[r].second << "\n";
                return;
            }else if(sum < MOD) l++;
            else r--;
        }
        cout << "-1\m";
        return;
    }

    // 4.没有0的情况且P!=0（寻找逆元的两数之和）
    long long S = 1;
    for(int i = 1; i <= n; i++) S = (S * (a[i] % MOD)) % MOD;
    long long C = (P * inv(S)) % MOD;
    vector<pair<long long, int>> v(n);
    for (int i = 1; i <= n; i++) {
        v[i - 1] = {inv(a[i]), i};
    }
    sort(v.begin(), v.end());
    // 二分查找和为C
    for(int i = 0; i < n; i++){
        long long target = (C - v[i].first + MOD) % MOD;
        auto it = lower_bound(v.begin(), v.end(), make_pair(target, 0));
        while(it != v.end() && it->first == target){
            if(it->second != v[i].second){
                cout << v[i].second << " " << it->second << "\n";
                return;
            }
            it++;
        }
    }
    cout << "-1\n";
}

int main() {
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}