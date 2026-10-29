/*
374. 猜数字大小

我们正在玩猜数字游戏。猜数字游戏的规则如下：

我会从 1 到 n 随机选择一个数字。 请你猜选出的是哪个数字。（我选的数字在整个游戏中保持不变）。

如果你猜错了，我会告诉你，我选出的数字比你猜测的数字大了还是小了。

你可以通过调用一个预先定义好的接口 int guess(int num) 来获取猜测结果，返回值一共有三种可能的情况：

-1：你猜的数字比我选出的数字大 （即 num > pick）。
1：你猜的数字比我选出的数字小 （即 num < pick）。
0：你猜的数字与我选出的数字相等。（即 num == pick）。
返回我选出的数字。
*/
#include <bits/stdc++.h>
using namespace std;

static int secret_pick;

int guess(int num) {
    if(num > secret_pick) return -1;
    if(num < secret_pick) return 1;
    return 0;
}

int guessNumber(int n) {
    int l = 0, r = n;
    while(l <= r){
        int mid = l + (r - l) / 2;
        int res = guess(mid);
        if(res == 0) return mid;
        else if(res > 0) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int main(){
    int n;
    while(cin >> n >> secret_pick){
        cout << guessNumber(n) << "\n";
    }
    return 0;
}