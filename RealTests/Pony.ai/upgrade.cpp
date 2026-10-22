/*
POPO希望把自己的祖传依赖升级到最新版来使用炫酷的新功能，但是由于时间太久，POPO的软件已经不支持直接升级最新版。
POPO希望找到一个方案能用最少的升级次数用上最新版:
每个新版软件都有一个最小兼容版本，只有当前版本号大于等于某个新版的最小兼容版本，POPO才能把软件升级到这个新版本上。
所有软件版本号格式均为a.b.c (0<=a,b,c<=1e^9)。
对于版本号a,b,c,d,e,f,果有(a>d)|| (a==d && b>e)||(a==d && b==e &&c>f)，我们就认为a.b.c大于d.e.f。

输入格式：
第一行两个版本号，代表POPO当前使用的软件版本和期望升级到的版本。
接下来一行一个整数n，代表候选软件版本数。
接下来n行，每行两个版本号，代表候选软件版本和该版本的最小兼容版本。

输入样例：
0.0.1 1.0.0
7
0.0.2 0.0.1
0.0.3 0.0.2
0.0.4 0.0.3
0.1.0 0.0.1
0.2.0 0.0.4
0.3.0 0.2.0
1.0.0 0.2.0

输出格式：
第一行一个整数m，代表POPO需要的最小升级次数。
接下来m行，每行一个版本号，代表POPO的升级次数。

输出样例：
3
0.1.0
0.2.0
1.0.0

注意：用例保证最终规则中一定包含精确的目标版本号，同时需要严格满足当前版本等于目标版本才算更新成功，大于不成立。

方法一：排序+贪心+剪枝
时间复杂度：排序O(NlogN)，搜索O(N)，总时间复杂度O(NlogN)
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

// std::tie 会把引用打包成一个临时元组 std::tuple<long long&, long long&, long long&>
// std::tuple 默认按照字典序比较大小，天然符合题目对版本号大小的比较定义
// 运算符重载
struct Version{
    long long a, b, c;
    string str;
    bool operator<(const Version& o) const {
        return tie(a, b, c) < tie(o.a, o.b, o.c);
    }
    bool operator>(const Version& o) const {
        return tie(a, b, c) > tie(o.a, o.b, o.c);
    }
    bool operator<=(const Version& o) const {
        return tie(a, b, c) <= tie(o.a, o.b, o.c);
    }
    bool operator==(const Version& o) const {
        return tie(a, b, c) == tie(o.a, o.b, o.c);
    }
};

struct Upgrade{
    Version to_ver;
    Version min_compact;
};

// 解析a.b.c格式的字符串
// 利用sstream自动解析字符串，遇到long long保存a、b、c，遇到char就代表'.'
Version parseVersion(const string& s){
    long long a, b, c;
    char dot1, dot2;
    stringstream ss(s);
    ss >> a >> dot1 >> b >> dot2 >> c;
    return {a, b, c, s};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string start_str, target_str;
    cin >> start_str >> target_str;
    Version start = parseVersion(start_str);
    Version target = parseVersion(target_str);
    int n ;
    cin >> n;
    vector<Upgrade> rules;
    for(int i = 0; i < n; i++){
        string to_str, min_str;
        cin >> to_str >> min_str;
        // 剪枝1：如果更新版本比target大，直接丢弃
        rules.push_back({parseVersion(to_str), parseVersion(min_str)});
    }
    if(start == target){
        cout << 0 << "\n";
        return 0;
    }
    // 按最小兼容版本升序
    sort(rules.begin(), rules.end(), [](const Upgrade& x, const Upgrade& y) {
        return x.min_compact < y.min_compact;
    });
    Version cur = start;
    vector<string> path;
    int idx = 0;
    int m = rules.size();
    Version best_available = start; // 当前已解锁规则中能够更新的最高版本
    while(!(cur == target)){
        bool can_reach_target = false;
        while(idx < m && rules[idx].min_compact <= cur){
            if(rules[idx].to_ver == target) can_reach_target = true;
            if(rules[idx].to_ver > best_available) best_available = rules[idx].to_ver;
            idx++; // 剪枝2，后续不需要再判断
        }
        if(can_reach_target){
            path.push_back(target.str);
            break;
        }
        if(best_available <= cur){
            cout << -1 << "\n";
            return 0;
        }
        cur = best_available;
        path.push_back(cur.str);
    }
    cout << path.size() << "\n";
    for(const string& s : path) cout << s << "\n";
    return 0;
}