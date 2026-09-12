/*
牛牛的工作是排雷，为了检验牛牛的专业能力，教官安排了以下测试:
在一块n x m的测试区域内，牛牛不能走出这块区域，初始位于坐标(x，y)处，牛牛只能朝上下左右四个方向移动，每移动一个单位距离耗费一个单位时间;同时已知在坐标(x2，y2)处埋有一枚地雷，这枚地雷的周围八个位置中的任意一个都可以作为排雷点，假设到达排雷点花费的最小用时为t，那么，排除这枚地雷就需要耗费(x1 × x2)^t^(y1 × y2)个单位时间，其中，^符号代表异或运算。
现在，牛牛在规划路线，而你需要更进一步，直接给出排雷耗时。

输入描述：
本题为多组测试数据。第一行输入一个正整数T(1≤T≤100)，代表测试数据的组数。
对于每组测试数据，第一行输入两个正整数n，m(2≤n，m≤100)，依次代表测试区域的行、列宽度。
第二行输入四个正整数，x1,y1,x2,y2(1≤x1,x2≤n;1≤y1,y2≤m)代表牛牛初始位于(x1，y1)位置，地雷位于(x2，y2)位置。
接下去n行，每行输入m个字符，用字符.表示这个位置可以到达，用字符#代表这个位置上有障碍物，无法到达。
数据保证，起始点以及埋雷点不重叠，且不会在障碍物上。

输出描述：
每一行输出排雷耗时。
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int landmine(vector<vector<char>>& grid, int x1, int y1, int x2, int y2){
    int n = grid.size() - 1;
    int m = grid[0].size() - 1;
    // dist[i][j] 表示从起点到 (i,j) 的最短距离
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, -1));
    queue<pair<int, int>> q;
    q.push({x1, y1});
    dist[x1][y1] = 0;
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    int t = -1;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 当前位置不是地雷周围八格之一
        if(abs(x - x2) <= 1 && abs(y - y2) <= 1 && !(x == x2 && y == y2)){
            t = dist[x][y];
            break;
        }

        // 上下左右移动
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if(grid[nx][ny] == '#') continue;
            if(dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    // 无法到达地雷周围任何一个位置
    if (t == -1) return -1;
    return (x1 * x2) ^ t ^ (y1 * y2);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        vector<vector<char>> grid(n + 1, vector<char>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> grid[i][j];
            }
        }
        cout << landmine(grid, x1, y1, x2, y2) << "\n";
    }
    return 0;
}