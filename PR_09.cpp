#include <iostream>
#include <vector>
using namespace std;

#define SPACE 10
int count = 1;

class node{
public:
	int key;
	string value;
	node *left;
	node *right;

	node(){
		key = 0;
		value = "";
		left = nullptr;
		right = nullptr;
	}
};

class AVLTree{
public:
	node *root;
	AVLTree(){
		root = nullptr;
	}

	bool isTreeEmpty(){
		if(root == nullptr) return true;
		else return false;
	}

	int height(node *node){
		if(node == nullptr) return -1;
		else {
			int lheight = height(node->left);
			int rheight = height(node->right);

			if(lheight > rheight) return lheight + 1;
			else return rheight + 1;
		}
	}

	int getBalanceFactor(node *node){
		if(node == nullptr){
			return -1;
		}
		else {
			return height(node->left) - height(node->right);
		}
	}

	node *rightRotate(node *n){
		node *left = n->left;
		node *leftright = left->right;

		left->right = n;
		n->left = leftright;
		return left;
	}

	node *leftRotate(node *n){
		node *right = n->right;
		node *rightleft = right->left;

		right->left = n;
		n->right = rightleft;
		return right;
	}

	node *insert(node *n, node *newnode){
		if(n == nullptr){
			n = newnode;
			cout << "Key " << newnode->key << " inserted succesfully!" << endl;
			return n;
		}

		if(newnode->key < n->key){
			n->left = insert(n->left, newnode);
		}
		else if(newnode->key > n->key){
			n->right = insert(n->right, newnode);
		}
		else {
			cout << "No duplicate values allowed" << endl;
			return n;
		}

		int bf = getBalanceFactor(n);

		// Left Left
		if(bf > 1 && newnode->key < n->left->key){
			return rightRotate(n);
		}

		// Right right
		if(bf < -1 && newnode->key > n->right->key){
			return leftRotate(n);
		}

		// Left right
		if(bf > 1 && newnode->key > n->left->key){
			n->left = leftRotate(n->left);
			return rightRotate(n);
		}

		// Right left
		if(bf < -1 && newnode->key < n->right->key){
			n->right = rightRotate(n->right);
			return leftRotate(n);
		}
		return n;
	}

	void print2D(node *n, int space){
		if(n == nullptr) return;

		space += SPACE;
		print2D(n->right, space);
		cout << endl;

		for(int i = SPACE; i < space; i++)
			cout << " ";

		cout << n->key << "\n";
		print2D(n->left, space);
	}

	node *search(node *n, int key){
		if(n == nullptr || n->key == key)
			return n;

		if(key < n->key){
			return search(n->left, key);
		}
		else{
			return search(n->right, key);
		}
	}
};

int main() {
	AVLTree tree;

	int choice, k;
	int searchKey;
	int flag = 1;

	while(flag == 1){
		cout << "======================= MENU ======================" << endl;
		cout << "1. Insert Node" << endl;
		cout << "2. Search Node" << endl;
		cout << "3. Display Tree" << endl;
		cout << "4. Exit" << endl;
		cout << "Choose an option: ";
		cin >> choice;

		node *newnode = new node();

		switch(choice){
		case 1:
			cout << "Enter the key: ";
			cin >> k;
			newnode->key = k;
			// allKeys.push_back(k);
			cout << "Enter the value: ";
			cin >> newnode->value;
			tree.root = tree.insert(tree.root, newnode);
			break;

		case 2:
			cout << "Enter key to search for: ";
			cin >> searchKey;
			newnode = tree.search(tree.root, searchKey);
			if(newnode) cout << "Value found " << endl;
			else cout << "Value not found" << endl;
			break;

		case 3:
			tree.print2D(tree.root, 0);
			break;

		case 4:
			flag = 0;
			cout << "====================== THANK YOU ====================" << endl;
			break;

		default:
			cout << "Invalid selection of option." << endl;
			break;
		}
	}
	return 0;
}