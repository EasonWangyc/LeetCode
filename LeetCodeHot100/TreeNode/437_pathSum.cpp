/*
437. 路径总和Ⅲ

给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// 二叉树节点结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 递归 DFS 函数：前缀和 + 状态回溯
void dfs(TreeNode* node, long long s, int targetSum, unordered_map<long long,  
         int>& cnt, int& ans) {
    if(node == nullptr) return ;
    // 1. 累加当前路径前缀和
    s += node->val;

    // 2. 查找是否存在祖先节点的前缀和满足：s - targetSum
    auto it = cnt.find(s - targetSum);
    if(it != cnt.end()) ans += it->second;

    // 3. 将当前前缀和加入哈希表，供子孙节点查询
    cnt[s]++;

    // 4. 递归处理左右子树
    dfs(node->left, s, targetSum, cnt, ans);
    dfs(node->right, s, targetSum, cnt, ans);

    // 5. 回溯清理：离开当前节点时，当前前缀和不再有效，恢复现场
    cnt[s]--;
}

// 主求解函数
int pathSum(TreeNode* root, int targetSum) {
    unordered_map<long long, int> cnt;
    // 关键基准点：前缀和为 0 出现 1 次（处理从 root 直达某节点的完整路径）
    cnt[0] = 1;
    int ans = 0;

    dfs(root, 0, targetSum, cnt, ans);
    return ans;
}

TreeNode* buildTreeNode(const vector<string>& nodes){
    if(nodes.empty() || nodes[0] == "null") return nullptr;
    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    int index = 1;
    while(!nodeQueue.empty() && index < nodes.size()){
        TreeNode* cur = nodeQueue.front();
        nodeQueue.pop();
        if(index < nodes.size() && nodes[index] != "null"){
            cur->left = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(cur->left);
        }
        index++;
        if(index < nodes.size() && nodes[index] != "null"){
            cur->right = new TreeNode(stoi(nodes[index]));
            nodeQueue.push(cur->right);
        }
        index++;
    }
    return root;
}

int main() {
    // 对应树形：
    //            10
    //           /  \
    //          5   -3
    //         / \     \
    //        3   2     11
    //       / \   \
    //      3  -2   1
    vector<string> treeData = {"10", "5", "-3", "3", "2", "null", "11", "3", "-2", "null", "1"};
    TreeNode* root = buildTreeNode(treeData);

    int targetSum = 8;
    int result = pathSum(root, targetSum);

    cout <<  result << endl;
    // 输出预期：3 （路径分别为 5->3, 5->2->1, -3->11）
    return 0;
}