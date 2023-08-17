#include <iostream>
#include <vector>
using namespace std;
// TreeNode Class Template
template <typename T>
class TreeNode {
public:
	T data;
	TreeNode* left;
	TreeNode* right;
	TreeNode();
	TreeNode(int);
};

// Constructor
template <typename T>
TreeNode<T>::TreeNode() {
	data = 0;
	left = nullptr;
	right = nullptr;
}

// Parametrized Constructor
template <typename T>
TreeNode<T>::TreeNode(int value) {
	data = value;
	left = nullptr;
	right = nullptr;
}

// BinarySearchTree Class Template
template <typename T>
class BinarySearchTree {
public:
	TreeNode<T>* root;
	TreeNode<T>* newNode;
	BinarySearchTree();
	int height(TreeNode<T>*);
	void rotateLeft(TreeNode<T>*&);
	void rotateRightLeft(TreeNode<T>*&);
	void rotateRight(TreeNode<T>*&);
	void rotateLeftRight(TreeNode<T>*&);
	void printTree(TreeNode<T>*);
	void printLevel(TreeNode<T>*, int);
	bool isEmpty();
	TreeNode<T>* insert(int);
	TreeNode<T>* insert(TreeNode<T>*&, int);
};

// Constructor
template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
	root = nullptr;
	newNode = nullptr;
}

// Get tree height by using root node and go through each level
template <typename T>
int BinarySearchTree<T>::height(TreeNode<T>* node) {
	// Height is 0 when root is null
	if (node == NULL)
		return 0;
	// Call height recursively to get height for left and right node
	int left = height(node->left);
	int right = height(node->right);

	// Return height after checking which height is higher
	if (left > right)
		return left + 1;
	else
		return right + 1;
}

// Rotate left to for tree balancing
template <typename T>
void BinarySearchTree<T>::rotateLeft(TreeNode<T>*& node) {
	TreeNode<T>*  nodePtr;

	// Set nodePtr equals to passed in node->left
	nodePtr = node->left;
	// Rotate by setting node->left equals to nodePtr->right
	node->left = nodePtr->right;
	// Set nodePtr-> equals to passed in node
	nodePtr->right = node;
	// Passed in node equals to nodePtr
	node = nodePtr;
}

// Rotate tree at node right left if needed for balancing
template <typename T>
void BinarySearchTree<T>::rotateRightLeft(TreeNode<T>*& node) {
	// Call rotate right and left once with node->left passed into
	// rotateright
	rotateRight(node->left);
	rotateLeft(node);
}

template <typename T>
void BinarySearchTree<T>::rotateRight(TreeNode<T>*& node) {
	TreeNode<T>* nodePtr;

	// Set nodePtr equals to passed in node->right
	nodePtr = node->right;
	// Rotate by setting node->right equals to nodePtr->left
	node->right = nodePtr->left;
	// Set nodePtr-> equals to passed in node
	nodePtr->left = node;
	// Passed in node equals to nodePtr
	node = nodePtr;
}

// Rotate tree at node left right if needed for balancing
template <typename T>
void BinarySearchTree<T>::rotateLeftRight(TreeNode<T>*& node) {
	// Call rotate left and right once with node->right being passed into
	// rotateleft
	rotateLeft(node->right);
	rotateRight(node);
}

// Insert value into tree while checking for empty tree
template <typename T>
TreeNode<T>* BinarySearchTree<T>::insert(int value) {
	// Check if tree is empty and set with root equals to value
	if (isEmpty()) 
		return (root = new TreeNode<T>(value));
	// Insert value into tree if tree is not empty
	else
		return insert(root, value);
}

// Check if tree is empty or not
template <typename T>
bool BinarySearchTree<T>::isEmpty() {
	// Return true when tree is empty
	if (root == NULL) return true;
	// Return false when tree is not empty
	else return false;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::insert(TreeNode<T>*& node, int value) {
	// Insert value into node when it is empty
	if (node == NULL)  
		node = new TreeNode<T>(value);
	// If value is less than node data/value, insert value 
	else if (value < node->data) {  
		insert(node->left, value);
		// Check height for rotation 
		if (height(node->left) - height(node->right) == 2) {
			// Rotate left once
			if (value < node->left->data)
				rotateLeft(node);
			// Rotate left twice if needed
			else
				rotateRightLeft(node);
		}
	}
	// If value is greater than node data/value, insert value
	else if (value > node->data) {
		insert(node->right, value);
		// Check height for rotaion
		if (height(node->right) - height(node->left) == 2) {
			// Rotate right once
			if (value > node->right->data)
				rotateRight(node);
			// Rotate right twice if needed
			else
				rotateLeftRight(node);
		}
	}
	return node;
}

// Print each nodes for each level
template <typename T>
void BinarySearchTree<T>::printTree(TreeNode<T>* root)
{
	// Create and initialize h by calling height function
	int h = height(root);;
	for (int index{ 1 }; index <= h; index++)
	{
		printLevel(root, index);
		cout << "\n";
	}
}

// Print nodes at a given level
template <typename T>
void BinarySearchTree<T>::printLevel(TreeNode<T>* root, int level)
{
	// Exit when root is empty
	if (root == NULL) {
		cout << "NULL ";
		return;
	}
	// When root level/height is 1, print root
	if (level == 1)
		cout << root->data << " ";
	// Print left/right nodes on the levels under root
	else if (level > 1)
	{
		printLevel(root->left, level - 1);
		printLevel(root->right, level - 1);
	}
}

int main() {
	cout << "Tree #1\n";
	// Test 1 with vector array 1 // 9 values/nodes
	BinarySearchTree<int> bst;
	vector<int> varray{ 18,16,14,12,10,8,6,4,2 };
	for (int index{ 0 }; index < (int)varray.size(); index++) {
		bst.insert(varray[index]);
	}
	bst.printTree(bst.root);

	cout << "\nTree #2\n";
	// Test 2 with vector array 2 // 10 values/nodes
	BinarySearchTree<int> bst2;
	vector<int> varray2{ 10,9,8,7,6,5,4,3,2,1 };
	for (int index{ 0 }; index < (int)varray2.size(); index++) {
		bst2.insert(varray2[index]);
	}
	bst2.printTree(bst2.root);
	return 0;
}