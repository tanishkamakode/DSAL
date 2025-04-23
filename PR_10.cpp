#include <iostream>
#include <vector>
using namespace std;

class BTNode {
public:
    int data;
    BTNode *left, *right;
} *Array[20];

class BTOperation {
public:
    BTOperation() {
        for (int i = 0; i < 20; i++) {
            Array[i] = nullptr;
        }
    }

    BTNode* createBT(BTNode* root) {
        int nodes, i, j, next, flag;
        BTNode* temp, *newNode;
        j = next = 0;

        cout << "How many nodes you want to insert in binary tree? : ";
        cin >> nodes;

        for (i = 0; i < nodes; i++) {
            flag = 0;
            newNode = new BTNode;

            cout << "Enter the node : ";
            cin >> newNode->data;
            newNode->left = newNode->right = nullptr;

            if (root == nullptr) {
                root = newNode;
                Array[j] = root;
                j++;
            }
            else {
                while (flag != 1) {
                    temp = Array[next];
                    if (temp->left == nullptr) {
                        temp->left = newNode;
                        Array[j] = temp->left;
                        j++;
                        flag = 1;
                    }
                    else if (temp->right == nullptr) {
                        temp->right = newNode;
                        Array[j] = temp->right;
                        j++;
                        flag = 1;
                    }
                    else {
                        next++;
                    }
                }
            }
        }
        return root;
    }

    void showBT() {
        int i;
        for (i = 0; Array[i] != nullptr && i < 20; i++) {
            cout << Array[i]->data << " ";
        }
    }

    void inorder(BTNode* root);
    void preorder(BTNode* root);
    void postorder(BTNode* root);
    void BTHeight(BTNode* root);
    void calcHeights(BTNode* root, vector<int>& heights, int count = 0);
    void mirror(BTNode* root);
    void countNodes(BTNode* root,int &internal,int &leaf);
    BTNode*  copyTree(BTNode* root);
//    void copy(BTNode* root,BTNode* new);
    void eraseTree(BTNode*& root);
    BTNode* createMinHeap(BTNode* root);
    BTNode* createMaxHeap(BTNode* root);
};
void BTOperation::inorder(BTNode* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void BTOperation::preorder(BTNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void BTOperation::postorder(BTNode* root) {
    if (root == nullptr) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void BTOperation::calcHeights(BTNode* root, vector<int>& heights, int count) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        heights.push_back(count);
        return;
    }

    calcHeights(root->left, heights, count + 1);
    calcHeights(root->right, heights, count + 1);
}


BTNode* BTOperation::createMinHeap(BTNode* root)
{
	if(root->left)
	{
		root->left=createMinHeap(root->left);
		if(root->left->data < root->data)
		{
			int temp=root->left->data;
			root->left->data=root->data;
			root->data=temp;
		}
	}

	if(root->right)
	{
		root->right=createMinHeap(root->right);
		if(root->right->data < root->data)
		{
			int temp=root->right->data;
			root->right->data=root->data;
			root->data=temp;
		}
	}

	return root;
}


BTNode* BTOperation::createMaxHeap(BTNode* root)
{
	if(root->left)
	{
		root->left=createMaxHeap(root->left);
		if(root->left->data > root->data)
		{
			int temp=root->left->data;
			root->left->data=root->data;
			root->data=temp;
		}
	}

	if(root->right)
	{
		root->right=createMaxHeap(root->right);
		if(root->right->data > root->data)
		{
			int temp=root->right->data;
			root->right->data=root->data;
			root->data=temp;
		}
	}

	return root;
}


int main() {
    cout << "\n\n********** Heap Sort **********\n\n" << endl;

    BTOperation tree;

    BTNode* root = nullptr;

    root = tree.createBT(root);

    cout << "Display using BFS : \n";
    tree.showBT();
    cout << endl;

    cout << "Display using inorder : \n";
    tree.inorder(root);
    cout << endl << endl;

//    cout << "Display using preorder : \n";
//    tree.preorder(root);
//    cout << endl << endl;
//
//    cout << "Display using postorder : \n";
//    tree.postorder(root);
//    cout << endl << endl;

    tree.createMinHeap(root);
    cout<<"\nMin heap: ";
    tree.preorder(root);

    cout<<"\nMinimum marks: "<<root->data;

    cout<<"\nMax heap: ";
    tree.createMaxHeap(root);
    tree.preorder(root);

    cout<<"\nMaximum marks: "<<root->data;

    return 0;
}