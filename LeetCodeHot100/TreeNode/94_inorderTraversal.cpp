/*
94. 二叉树的中序遍历

给定一个二叉树的根节点root，返回它的中序遍历。
*/
#include <iostream>
#include <queue>
#include <vector>
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

void dfs(TreeNode* root, vector<int>& res){
	if(!root) return;
	// “左-根-右”顺序
	dfs(root->left, res);
	res.push_back(root->val);
	dfs(root->right, res);
}

vector<int> inorderTraversal(TreeNode* root){
	vector<int> res;
	dfs(root, res);
	return res;
}

int main() {
    vector<string> nodes = {"1", "null", "2", "3"};
    TreeNode* root = buildTreeNode(nodes);
    vector<int> result = inorderTraversal(root);
    for (int val : result) cout << val << " ";
    cout << "\n";
    return 0;
}