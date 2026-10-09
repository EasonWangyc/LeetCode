/*
322. 零钱兑换

给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int coinsChange(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, amount + 1); // amount+1大小是为了取到amount，值为amount+1是为了最后判断能否组成
    dp[0] = 0;
    for(int i = 1; i <= amount; i++){
        for(int coin : coins){
            if(i >= coin) dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
    return dp[amount] == amount + 1 ? -1 : dp[amount];
}

int main(){
    vector<int> coins = {1, 2, 5};
    cout << coinsChange(coins, 11) << "\n";
    return 0;
}