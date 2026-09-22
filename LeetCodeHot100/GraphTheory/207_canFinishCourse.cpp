/*
207. 课程表

你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习，如果可以，返回 true ；否则，返回 false 。

思路：
1. 有向图：建立一条从bi指向ai的有向边
2. 度：度分为入度和出度，分别代表指向该节点的边数和该节点指出去的边数，inDegree[i]表示i的前置课程有哪些未完成
3. queue的作用：当前可以立即进行学习的课程列表，即入度为0

*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool canFinishCourse(int n, vector<vector<int>>& prerequisites){
    vector<vector<int>> adj(n);     // 创建有向图，[a, b]表示b->a
    vector<int> inDegree(n, 0);     // 创建度
    for(auto& pre : prerequisites){
        adj[pre[1]].push_back(pre[0]);
        inDegree[pre[0]]++;
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(inDegree[i] == 0) q.push(i);
    }
    int count = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        count++;
        // 遍历依赖cur的所有课程
        for(int next : adj[cur]){
            inDegree[next]--;
            if(inDegree[next] == 0) q.push(next);
        }
    }
    return count == n;
}

int main(){
    int n = 2;
    vector<vector<int>> prerequisites = {{1, 0}, {0, 1}};
    cout << canFinishCourse(n, prerequisites) << "\n";
    return 0;
}