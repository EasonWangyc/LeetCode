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

void printTree(TreeNode* root){
    if(!root) return;
    cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

TreeNode* invertTree(TreeNode* root){
    if(!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

int main(){
    vector<string> nodes = {"4", "2", "7", "1", "3", "6", "9"};
    TreeNode* root = buildTreeNode(nodes);
    root = invertTree(root);
    printTree(root);
    cout << endl;
    return 0;
}