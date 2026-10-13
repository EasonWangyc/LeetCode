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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    
}