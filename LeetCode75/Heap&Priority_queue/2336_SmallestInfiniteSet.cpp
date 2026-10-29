/*
2336. 无限集中的最小数字

现有一个包含所有正整数的集合 [1, 2, 3, 4, 5, ...] 。

实现 SmallestInfiniteSet 类：

SmallestInfiniteSet() 初始化 SmallestInfiniteSet 对象以包含 所有 正整数。
int popSmallest() 移除 并返回该无限集中的最小整数。
void addBack(int num) 如果正整数 num 不 存在于无限集中，则将一个 num 添加 到该无限集中。
*/
#include <bits/stdc++.h>
using namespace std;

class SmallestInfiniteSet {
private:
    int threshold;
    set<int> added;
public:
    SmallestInfiniteSet() {
        threshold = 1;
    }
    int popSmallest() {
        if(!added.empty()){
            int smallest = *added.begin();
            added.erase(added.begin());
            return smallest;
        }
        int smallest = threshold;
        threshold++;
        return smallest;
    }
    void addBack(int num) {
        if(num < threshold) added.insert(num);
    }
};

int main(){
    SmallestInfiniteSet sis;
    sis.addBack(2);
    cout << sis.popSmallest() << "\n";
    cout << sis.popSmallest() << "\n";
    cout << sis.popSmallest() << "\n";
    sis.addBack(1);
    cout << sis.popSmallest() << "\n";
    cout << sis.popSmallest() << "\n";
    cout << sis.popSmallest() << "\n";
    return 0;
}