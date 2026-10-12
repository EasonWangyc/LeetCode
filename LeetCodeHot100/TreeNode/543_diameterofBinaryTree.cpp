/*
543. 二叉树的直径

给定一棵二叉树，你需要计算它的直径长度。二叉树的直径长度是树中任意两个节点路径长度中的最大值。
这条路径可能穿过也可能不穿过根节点root。
两节点之间路径的 长度 由它们之间边数表示。
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

int getDepth(TreeNode* root, int& max_diameter){
	if(!root) return 0;
	int l = getDepth(root->left, max_diameter);
	int r = getDepth(root->right, max_diameter);
	// 对于一个节点，边数=最大深度-1，即减去当前节点，恰好能写成左右子树最大深度相加
	// 当前节点的左子树的最大深度和右子树的最大深度相加，不包含当前节点
	max_diameter = max(max_diameter, l + r);
	return max(l, r) + 1;
}

int diameterOfBinaryTree(TreeNode* root){
	int max_diameter = 0;
	getDepth(root, max_diameter);
	return max_diameter;
}

int main() {
    vector<string> nodes = {"1", "2", "3", "4", "5"};
    TreeNode* root = buildTreeNode(nodes);
	cout << diameterOfBinaryTree(root) << "\n";
    return 0;
}