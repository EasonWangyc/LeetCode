/*
1437.是否所有1都至少相邻k个元素

给你一个由若干个0和1组成的数组nums以及整数k，如果所有1都至少相隔k个元素，则返回true，否则返回false。
*/
#include <iostream>
#include <vector>
using namespace std;

bool apartKelements(vector<int>& nums, int k){
    int n = nums.size();
    int back = INT8_MIN; // 初始化不能是0
    for(int i = 0; i < n; i++){
        if(nums[i] == 1){
            if(i - back < k) return false;
            back = i;
        }
    }
    return true;
}

int main(){
    vector<int> nums = {1, 0, 0, 0, 1, 0, 0, 1};
    cout << boolalpha; // 输出直接显示bool值
    cout << apartKelements(nums, 2) << "\n";
    return 0;
}