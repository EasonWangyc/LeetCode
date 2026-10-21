/*
给定一个整数，求它里面的最大递减数，如95345432里面的递减数有953 53 5432 543 532 54 43 32，最大递减数为5432。
*/
#include <bits/stdc++.h>
using namespace std;

long long maxDecreasingNumber(long long num){
    string s = to_string(num);
    int n = s.length();
    long long ans = INT_MIN;
    string ref = "";
    ref += s[0];
    for(int i = 1; i < n; i++){
        if(s[i] < s[i - 1]){
            ref += s[i];
        }
        else{
            ans = max(ans, stoll(ref));
            ref.clear();
            ref += s[i];
        }
    }
    return max(ans, stoll(ref));
}

int main(){
    long long num = 95345432;
    cout << maxDecreasingNumber(num) << "\n";
    return 0;
}