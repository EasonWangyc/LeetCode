#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode{
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

int maxDepth(TreeNode* root){
    if(!root) return 0;
    int l = maxDepth(root->left);
    int r = maxDepth(root->right);
    return max(l, r) + 1;
}

int main(){
    vector<string> nodes = {"3", "9", "20", "null", "null", "15", "7"};
    TreeNode* root = buildTreeNode(nodes);
    cout << maxDepth(root) << "\n";
    return 0;
}