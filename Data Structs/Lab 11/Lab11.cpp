#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

template<class T>
class BinSTree {
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node(T item) : data(item), left(nullptr), right(nullptr) {}
	};

	Node* root;

public:
	BinSTree() {
		root = NULL;
	}

	void insert_to_tree(T item) {
		root = insert_to_tree(root, item);
	}

	bool isInTree(T item) {
		int counter = 0;
		return isInTree(root, item, counter);
	}

	Node* returnRoot() {
		return root;
	}

	int maxDepth(Node* node) {
		if(node == NULL) {
			return 0;
		}
		else {
			int lDepth = maxDepth(node->left);
			int rDepth = maxDepth(node->right);

			if (lDepth > rDepth) {
				return (lDepth + 1);
			}
			else {
				return (rDepth + 1);
			}
		}
	}

	int minDepth(Node* node) {
		if (node == NULL) {
			return 0;
		}
		if (node->left == NULL && node->right == NULL) {
			return 1;
		}

		int leftBranch = INT_MAX, rightBranch = INT_MAX;

		if (node->left) {
			leftBranch = minDepth(node->left);
		}
		if (node->right) {
			rightBranch = minDepth(node->right);
		}

		return min(leftBranch, rightBranch) + 1;
	}

private:
	Node* insert_to_tree(Node* node, T item) {
		if (node == NULL) {
			node = new Node(item);
			node->data = item;
			node->left = node->right = NULL;
		}
		else if (item < node->data) {
			node->left = insert_to_tree(node->left, item);
		}
		else if (item > node->data) {
			node->right = insert_to_tree(node->right, item);
		}
		return node;
	}

	bool isInTree(Node* node, T item, int& counter) {
		if (node == NULL) {
			cout << "\nNot found " << item << " in " << counter << " comparisons.\n\n";
			return false;
		}
		if (node->data == item) {
			cout << "\nFound " << item << " in " << counter << " comparisons.\n\n";
			return true;
		}
		else if (item < node->data) {
			counter++;
			return isInTree(node->left, item, counter);
		}
		else if (item > node->data) {
			counter++;
			return isInTree(node->right, item, counter);
		}
		return false;
	}
};

int main() {
	BinSTree<int> tree;
	int i;
	srand(time(NULL));

	for (i = 0; i < 10000; i++) { 
		tree.insert_to_tree(rand() % 10000);
	}
	
	cout << "Root: " << tree.returnRoot()->data << endl;
	cout << "Max depth of tree: " << tree.maxDepth(tree.returnRoot()) << endl;
	cout << "Min depth of tree: " << tree.minDepth(tree.returnRoot()) << endl;

	while (true) {
		cout << "Search for a number (0-9999): ";
		int num;
		cin >> num;
		tree.isInTree(num);
	}

	return 0;
}

