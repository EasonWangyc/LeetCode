/*
小明有一个长度为n的正整数数组a。每次操作他可以选择一对相邻元素，将它们合并为一个新元素，新元素的值为两者之和。
小明想让数组变为单调不减(即对于所有相邻元素满足a_i≤a_{i+1})。请你帮他求出最少需要多少次操作。

输入描述：
第一行一个正整数T，表示测试数据组数。
对于每组测试数据:第一行一个正整数n，表示数组长度。第二行n个正整数aa2....a表示数组元素。1sn≤5000, 1≤a;≤109,1≤T≤25

输出描述：
对于每组测试数据，输出一行一个整数，表示最少操作次数。

样例输入：
3
4
3 1 2 4
4
1 2 3 4
5
4 2 3 1 5

样例输出：
1
0
2

思路：遍历i，向前寻找最后一个分界点j。
dp[i]：前i个数能切出的最多段数。
last[i]：前i个数在取得最多段数的前提下，最后一段的和（为了给后续数字留出最大的上升空间，这个和越小越好）。
计算当前位置i时：从i - 1倒序枚举上一个切分点j（即假设最后一段是 (j, i]）：当前段和 = s[i] - s[j]
贪心最优性：只要我们倒着找，第一个满足 s[i] - s[j] >= last[j] 的 j，就是让最后一段尽可能短、且段数最多的最优解。
找到这个j后，直接更新：dp[i] = dp[j] + last[i] = s[i] - s[j]立即 break 结束内层循环（贪心剪枝）。

以[3, 1, 2, 4]为例，s=[0, 3, 4, 6, 10]：
i=1，j=0，当前段和s[1] - s[0] = 3 >= last[0](0)，更新dp[1]=dp[0]+1=1和last[1]=3；
i=2，j=1，当前段和s[2] - s[1] = 1 < last[1](3)，不成立。
i=2，j=0，当前段和s[2] - s[0] = 4 >= last[0](0)，更新dp[2]=dp[0]+1=1和last[2]=4；
i=3，j=2，当前段和s[3] - s[2] = 2 < last[2](4)，不成立。
i=4，j=1，当前段和s[3] - s[1] = 3 >= last[1](3)，更新dp[3]=dp[1]+1=2和last[3]=3；
i=4，j=3，当前段和s[4] - s[3] = 4 >= last[3](3)，更新dp[4]=dp[3]+1=3和last[4]=4。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int monotonic(vector<long long>& nums, int n){
    vector<long long> s(n + 1, 0);
    for(int i = 1; i <= n; i++) s[i] = s[i - 1] + nums[i];
    vector<int> dp(n + 1, 0);
    vector<long long> last(n + 1, 0);
    for(int i = 1; i <=n; i++){
        for(int j = i - 1; j >= 0; j--){
            long long cur_sum = s[i] - s[j];
            if(cur_sum >= last[j]){
                dp[i] = dp[j] + 1;
                last[i] = cur_sum;
                break;
            }
        }
    }
    return n - dp[n];
}

int main() {
    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int n;
        cin >> n;
        vector<long long> nums(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            cin >> nums[i];
        }
        cout << monotonic(nums, n) << "\n";
    }

    return 0;
}