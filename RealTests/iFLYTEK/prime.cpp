/*
批量求 $[1, N]$ 内所有质数。
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> linear_sieve(int n){
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= n; i++){
        if(is_prime[i]) primes.push_back(i);
        for(int p : primes){
            if(i * p > n) break;
            is_prime[i * p] = false;
            // 核心剪枝：如果 i 能被 p 整除，说明 p 是 i 的最小质因子。
            // 此时对于后续更大的质数 p'，i * p' 的最小质因子依然是 p 而非 p'，
            // 为了防止被重复标记，必须立刻 break 退出。
            if(i % p == 0) break;
        }
    }
    return primes;
}

int main(){
    vector<int> primes = linear_sieve(100);
    for(int num : primes) cout << num << " ";
    cout << "\n";
    return 0;
}