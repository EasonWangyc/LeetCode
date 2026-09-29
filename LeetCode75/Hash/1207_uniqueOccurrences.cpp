/*
1207. 独一无二的出现次数

给你一个整数数组 arr，如果每个数的出现次数都是独一无二的，就返回 true；否则返回 false。
*/
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
using namespace std;

bool uniqueOccurrences(vector<int>& arr){
    unordered_map<int, int> frequency;
    for(int num : arr) frequency[num]++;
    unordered_set<int> set;
    for(auto& pair : frequency){
        if(set.count(pair.second)) return false;
        set.insert(pair.second);
    }
    return true;
}

int main(){
    vector<int> arr = {1, 2, 2, 3, 3, 3};
    cout << boolalpha << uniqueOccurrences(arr) << "\n";
    return 0;
}