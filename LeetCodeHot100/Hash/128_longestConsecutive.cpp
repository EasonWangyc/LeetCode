/*
128. 最长连续序列

给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
*/
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int longestConsecutive(vector<int>& nums){
    // 该写法实现去重+O(1)查找
    // 在 C++ 标准库中，std::unordered_set 普遍采用拉链法（Separate Chaining，开链法）
    // 实现：底层是一段连续的数组（称为桶数组，Buckets），每个桶位置存放一个单向链表。
    // 元素插入时采用取模的方法，如果结果位置上无元素，放入；如果有，接着链表放置
    // 以nums = [100, 4, 200, 1, 3, 2]为例：
    /*
        桶索引 (Bucket Array)         单向链表节点 (Node: [Value | Next Pointer])
    ┌───────────┐
    │ Bucket[0] │ ──> nullptr
    ├───────────┤
    │ Bucket[1] │ ──> [ 1   | nullptr ]
    ├───────────┤
    │ Bucket[2] │ ──> [ 2   | *next ] ──> [ 100 | nullptr ]
    ├───────────┤
    │ Bucket[3] │ ──> [ 3   | nullptr ]
    ├───────────┤
    │ Bucket[4] │ ──> [ 200 | *next ] ──> [ 4   | nullptr ]
    ├───────────┤
    │ Bucket[5] │ ──> nullptr
    ├───────────┤
    │ Bucket[6] │ ──> nullptr
    └───────────┘
    */
    unordered_set<int> st(nums.begin(), nums.end());
    int ans = 0;
    for(int x : st){
        if(st.count(x - 1)) continue; // 剪枝：如果x-1在set中，那么x肯定不是某个连续序列的起点
        int y = x + 1;
        while(st.count(y)){
            y++;
        }
        ans = max(y - x, ans);
    }
    return ans;
}

int main(){
    vector<int> nums = {100, 2, 200, 1, 3, 4};
    cout << longestConsecutive(nums) << "\n";
    return 0;
}