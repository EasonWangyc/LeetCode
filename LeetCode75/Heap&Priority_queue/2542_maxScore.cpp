/*
2542. 最大子序列的分数

给你两个下标从 0 开始的整数数组 nums1 和 nums2 ，两者长度都是 n ，再给你一个正整数 k 。你必须从 nums1 中选一个长度为 k 的 子序列 对应的下标。

对于选择的下标 i0 ，i1 ，...， ik - 1 ，你的 分数 定义如下：

nums1 中下标对应元素求和，乘以 nums2 中下标对应元素的 最小值 。
用公式表示： (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]) 。
请你返回 最大 可能的分数。

一个数组的 子序列 下标是集合 {0, 1, ..., n-1} 中删除若干元素得到的剩余集合，也可以不删除任何元素。

思路：根据i将nums1元素和nums2元素配对，按照nums2元素大小降序排列
*/
#include <bits/stdc++.h>
using namespace std;

long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
    int n = nums1.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return nums2[i] > nums2[j];
    });
    priority_queue<int, vector<int>, greater<int>> min_heap;
    long long sum1 = 0;
    long long max_score = 0;
    // 对于某一个i，之前所有的元素都能保证nums2值都大于当前值，只需要考虑nums1的和
    for(int i : idx){
        int x = nums1[i], y = nums2[i];
        sum1 += x;
        min_heap.push(x);
        if(min_heap.size() > k){
            sum1 -= min_heap.top();
            min_heap.pop();
        }
        if(min_heap.size() == k){
            max_score = max(max_score, sum1 * y);
        }
    }
    return max_score;
}

int main(){
    vector<int> nums1 = {1, 3, 3, 2};
    vector<int> nums2 = {2, 1, 3, 4};
    cout << maxScore(nums1, nums2, 3) << "\n";
    return 0;
}