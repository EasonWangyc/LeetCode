/*
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

测试用例保证输出的长度不会超过 $10^5$。

示例：
输入：s = "3[a]2[bc]"
输出："aaabcbc"

思路：用一个栈来保护每一层的字符串和重复次数，当遇到数字时记录重复次数，当遇到 `[` 时将当前字符串和重复次数入栈，当遇到 `]` 时出栈并将当前字符串重复相应次数后拼接到栈顶字符串上。

注意：`isdigit()` 方法可以用来判断当前字符是否为数字；需要考虑多位整数的情况；`if`、`else if`和`else`的联合使用。
*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

string decodestring(string s){
    string res = " ";
    long long multi = 0;
    stack<int> numStack;
    stack<string> strStack;
    for(char c : s){
        if(isdigit(c)) multi = multi * 10 + (c - '0');
        else if(c == '['){
            numStack.push(multi);
            strStack.push(res);
            multi = 0;
            res = "";
        }
        else if(c == ']'){
            int k = numStack.top();
            numStack.pop();
            string last_res = strStack.top();
            strStack.pop();
            string temp = "";
            for(int i = 0; i < k; i++){
                temp += res;
            }
            res = last_res + temp;
        }
        else res += c;
    }
    return res;
}

int main(){
    string s = "3[a2[c]]";
    cout << decodestring(s) << "\n";
    return 0;
}