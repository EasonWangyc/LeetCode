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

bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr || q == nullptr) {
        return p == q;
    }
    return p->val == q->val && isSameTree(p->left, q->right) && isSameTree(p->right, q->left);
}

bool isSymmetric(TreeNode* root) {
    return isSameTree(root->left, root->right);    
}

int main() {
    vector<string> nodes = {"1", "2", "2", "3", "4", "4", "3"};
    TreeNode* root = buildTreeNode(nodes);
    cout << boolalpha << isSymmetric(root) << "\n";
    return 0;
}