/*
443. 压缩字符串

给你一个字符数组 chars ，请使用下述算法压缩：
从一个空字符串 s 开始。对于 chars 中的每组 连续重复字符 ：
如果这一组长度为 1 ，则将字符追加到 s 中。
否则，需要向 s 追加字符，后跟这一组的长度。
压缩后得到的字符串 s 不应该直接返回 ，需要转储到字符数组 chars 中。需要注意的是，如果组长度为 10 或 10 以上，则在 chars 数组中会被拆分为多个字符。
请在 修改完输入数组后 ，返回该数组的新长度。
你必须设计并实现一个只使用常量额外空间的算法来解决此问题。
注意：数组中超出返回长度的字符无关紧要，应予忽略。

示例：
输入：chars = ["a","a","b","b","c","c","c"]
输出：6
解释：分组是 "aa"、"bb" 和 "ccc"，压缩为 "a2b2c3"。
在原地修改输入数组之后，chars 的前 6 个字符应为 ["a","2","b","2","c","3"]。

思路：双指针，left表示当前字符出现的第一个位置，一个表示长度
*/
#include <iostream>
#include <vector>
using namespace std;

int compress(vector<char>& chars){
    int n = chars.size();
    int left = 0, len = 0;
    for(int i = 0; i < n; i++){
        if(i == n - 1 || chars[i] != chars[i + 1]){
            chars[len++] = chars[i];
            int nums = i - left + 1;
            if(nums > 1){
                // 考虑到多位数的情况
                for(char c : to_string(nums)) chars[len++] = c;
            }
            left = i + 1;
        }
    }
    return len;
}

int main(){
    vector<char> chars = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b', 'c'};
    cout << compress(chars) << "\n";
    for(char c : chars) cout << c << " ";
    cout << "\n";
    return 0;
}