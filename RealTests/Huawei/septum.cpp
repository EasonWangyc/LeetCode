/*
将一个由数字字符组成的字符串转换成七进制数。
*/
#include <bits/stdc++.h>
using namespace std;

string septum(string s){
    if(s.empty()) return "";
    long long num = stoll(s);
    if(num == 0) return "0";
    bool is_negative = num < 0;
    if(is_negative) num = -num;
    string result = "";
    while(num > 0){
        result += to_string(num % 7);
        num /= 7; 
    }
    reverse(result.begin(), result.end());
    if(is_negative) result = '-' + result;
    return result;
}

int main(){
    cout << septum("-102") << " " << septum("231") << " " << septum("49") << "\n";
    return 0;
}