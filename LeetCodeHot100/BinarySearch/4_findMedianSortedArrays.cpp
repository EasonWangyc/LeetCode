/*
4. 寻找两个正序数组的中位数

给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
算法的时间复杂度应该为 O(log (m+n)) 。

思路：如果两数组总长度m + n为奇数，中位数就是第(m + n + 1) / 2小的数；如果总长度为偶数，中位数就是第 (m + n + 1) / 2 小与第 (m + n + 2) / 2 小的平均值。

核心判断：对于nums1和nums2，其实就是找到两个合并排序后的第k小的元素，先比较两个数组的第k/2个元素，如果nums1值小，说明nums1的k/2索引之前的元素都不可能是第k小的元素，可以直接淘汰，反之亦然。
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

// 在两个数组中找到第k个小的数
// i和j分别表示nums1和nums2当前有效的起始下标
int findKth(const vector<int>& nums1, const vector<int>& nums2, int i, int j, int k){
    // 边界1：nums1空
    if(i >= nums1.size()) return nums2[j + k - 1];
    // 边界2：nums2空
    if(j >= nums2.size()) return nums1[i + k - 1];
    // 边界3：k=1
    if(k == 1) return min(nums1[i], nums2[j]);
    // 取各自的第k/2个元素进行比较，不够补INT_MAX
    int mid1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
    int mid2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
    if(mid1 <= mid2) return findKth(nums1, nums2, i + k / 2, j, k - k / 2);
    else return findKth(nums1, nums2, i, j + k / 2, k - k / 2);
}

double findMedianSortedArray(vector<int>& nums1, vector<int>& nums2){
    int total = nums1.size() + nums2.size();
    if(total % 2){
        int k = (total + 1) / 2;
        return findKth(nums1, nums2, 0, 0, k);
    }else{
        int k1 = total / 2;
        int k2 = total / 2 + 1;
        int mid1 = findKth(nums1, nums2, 0, 0, k1);
        int mid2 = findKth(nums1, nums2, 0, 0, k2);
        return (mid1 + mid2) / 2.0;
    }
}

int main(){
    vector<int> nums1 = {1, 2}, nums2 = {3, 4};
    cout << findMedianSortedArray(nums1, nums2) << "\n";
    return 0;
}