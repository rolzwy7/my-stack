#include "stdafx.h"

struct Node {
	Node *left;
	Node *right;
	int val;
};

void addElement(Node* &root, int val) {
	if (!root)
		root = new Node{ nullptr, nullptr, val };
	else if (val < root->val)
		addElement(root->left, val);
	else
		addElement(root->right, val);
}

void printTreeAsc(Node* root) {
	if(root) {
		printTreeAsc(root->left);
		printf("%d, ", root->val);
		printTreeAsc(root->right);
	}
}

void printTreeDesc(Node* root) {
	if (root) {
		printTreeDesc(root->right);
		printf("%d, ", root->val);
		printTreeDesc(root->left);
	}
}

void deleteTree(Node* &root) {
	if (root) {
		deleteTree(root->right);
		deleteTree(root->left);
		delete root;
	}

	root = nullptr;
}

int main() {
    return 0;
}

