/*
75. 颜色分类

给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
必须在不使用库内置的 sort 函数的情况下解决这个问题。
*/
#include <vector>
#include <iostream>
using namespace std;

void sortColors(vector<int>& nums){
    int n = nums.size();
    int red = 0, white = 0, blue = 0;
    for(int i = 0; i < n; i++){
        if(nums[i] == 0){
            nums[blue++] = 2;
            nums[white++] = 1;
            nums[red++] = 0;
        }else if(nums[i] == 1){
            nums[blue++] = 2;
            nums[white++] = 1;
        }else nums[blue++] = 2;
    }
}

int main(){
    vector<int> nums = {2, 0, 2, 0, 1, 1, 2};
    sortColors(nums);
    for(int num : nums) cout << num << " ";
    cout << "\n";
    return 0;
}