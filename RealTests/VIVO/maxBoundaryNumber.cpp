/*
给定一个长度为n的二进制字符串s(视为二元色带)，其中Si属于{0,1}。定义边界数为满足1≤i≤n一1且si;≠si+1的下标个数。
你可以进行不超过k次反色操作。一次反色操作为选择一个严格内部区间[L,R](满足2≤L≤R≤n-1)，并将所有i属于[L,R]的Si同时替换为1-si。
你的目标是在不超过k次操作后，使色带的边界数尽可能大。
请在不超过k次操作后，使边界数尽可能大，并输出可以达到的最大边界数。

输入描述：
每个测试文件包含多组测试数据。第一行输入一个整数T(1≤T≤10^5)表示数据组数，每组测试数据描述如下:
第一行输入两个整数n,k(2≤n≤2x10^5,0≤k≤2x10^5)；
第二行输入一个长度为n的二进制字符串s，仅包含字符'0'与'1'；
保证所有测试数据的n之和不超过2x10^5。

输入示例：
2
7 2
0110111
6 2
111111

输出示例：
5
4

思路：
1. s1和sn永远不会被翻转
2. 每次翻转[L,R]区间，其内部所有相邻字符的相对关系不变，受到改变的仅有两个切分点：{L-1,L}和{R,R+1}
- 若两个切分点均为非“边界”，则边界数+2
- 若两个切分点一个为边界一个为非边界，边界总数不变
- 若两个切分边均为“边界”，则边界数-2
即：每次操作至多让边界数+2，且边界数的奇偶性不会发生变化
3. 边界奇偶性与两端的关系：
- 若s1=sn，最终边界数一定是偶数
- 若s1!=sn，最终边界数一定是奇数
4. 上限分析：对于一个长度为n的字符串，边界最大值为n-1
- n-1的奇偶性与两端字符情况兼容（如s1!=sn且n-1为奇数），上限limit=n-1
- n-1的奇偶性与两端字符情况不兼容（如s1=sn且n-1为奇数），上限limit=n-2

因此，最终答案 = min(B初始+2*k, limit)
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void maxBoundaryNumber(){
    int n;
    cin >> n;
    long long k;
    cin >> k;
    string s;
    cin >> s;
    int init_boundary = 0;
    for(int i = 0; i < n - 1; i++){
        if(s[i] != s[i + 1]) init_boundary++;
    }
    int limit = n - 1;
    if((limit % 2 ) != (init_boundary % 2)) limit = n - 2;
    long long ans = init_boundary + 2LL * k;
    ans = min(ans, (long long)limit);
    cout << ans << "\n";
}

int main(){
    int T;
    cin >> T;
    while(T--) maxBoundaryNumber();
    return 0;
}