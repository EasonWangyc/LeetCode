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

vector<int> dfs(TreeNode* root, vector<int>& result) {
	if (!root) {
		return result;
	}
	dfs(root->left, result);
	result.push_back(root->val);
	dfs(root->right, result);
	return result;
}

int main() {
    vector<string> nodes = {"1", "null", "2", "3"};
    TreeNode* root = buildTreeNode(nodes);
    vector<int> result;
    result = dfs(root, result);

    for (int val : result) {
        cout << val << " ";
    }
    cout << "\n";

    return 0;
}