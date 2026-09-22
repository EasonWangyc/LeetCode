/*
给定一棵二叉树，你需要计算它的直径长度。二叉树的直径长度是树中任意两个节点路径长度中的最大值。这条路径可能穿过也可能不穿过根节点。

示例：
输入：root = [1,2,3,4,5]
输出：3
解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。

思路：递归法。观察边的数量，若节点为空，返回-1；否则定义l为左侧子树当前节点的直径，r为右侧子树，每次递归左右子树的值+1，更新ans为max(ans, l + r)；更新全局变量diameter为当前直径和之前直径的较大值，然后返回当前节点的高度，即max(l, r) 。
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeNode(const vector<string>& nodes) {
	if (nodes.empty() || nodes[0] == "null") {
		return nullptr;
	}

	TreeNode* root = new TreeNode(stoi(nodes[0]));
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);
	int index = 1;

	while (!nodeQueue.empty() && index < static_cast<int>(nodes.size())) {
		TreeNode* current = nodeQueue.front();
		nodeQueue.pop();

		if (index < static_cast<int>(nodes.size()) && nodes[index] != "null") {
			current->left = new TreeNode(stoi(nodes[index]));
			nodeQueue.push(current->left);
		}
		++index;

		if (index < static_cast<int>(nodes.size()) && nodes[index] != "null") {
			current->right = new TreeNode(stoi(nodes[index]));
			nodeQueue.push(current->right);
		}
		++index;
	}

	return root;
}

int dfs(TreeNode* root, int& ans){
    if(root == nullptr) return -1;// 以边的数量为单位，所以空节点返回-1
    int l = dfs(root->left, ans) + 1;   // 以边的数量为单位，所以要加1
    int r = dfs(root->right, ans) + 1;  // 以边的数量为单位，所以要加1
    ans = max(ans, l + r);
    return max(l, r);// 返回以当前节点为根的子树的最大深度（以边的数量为单位）
}

int diameterOfBinaryTree(TreeNode* root) {
    int ans = 0;
    dfs(root, ans);
    return ans;
}

int main() {
    vector<string> nodes = {"1", "2", "3", "4", "5"};
    TreeNode* root = buildTreeNode(nodes);
    int result = diameterOfBinaryTree(root);
    cout << result << endl;
    return 0;
}