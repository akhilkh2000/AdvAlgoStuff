#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int key;
	int value;
	struct node* left, *right;
} node;

typedef struct dict {
	node* root;
} dict;



void* make_new_dictionary() {
	dict * d = malloc(sizeof(dict));
	d -> root = NULL;
	return d;
}

node*rotateLeft(node* r) {
	node* temp = r - > right;
	r -> right = temp ->left;
	temp -> left =  r;
	return temp;
}

node*rotateRight(node* r) {
	node* temp = r -> left;
	r->left = temp ->right;
	temp -> right  =  r;
	return  temp;

}

node* splay(node* root, int k) {
	if (!root || root ->key == NULL)
		return root;
	if (k < root->key) {
		//left subtree
		if (!root -> left) return root;

		//left-left
		if (k < root->left->key) {
			//recursively splay till key comes to root->left->left
			root->left->left = splay(root->left->left, k);
			//do one right rotation
			root = rotateRight(root);

		}
		else if (k > root->left->key) { //left - right
			root -> left -> right = splay(root -> left ->right, k);
			if (root ->left -> right)
				root -> left = rotateLeft(root->left);

		}

		if (root -> left == NULL) return root; //only one rotation
		else
			//second rotation
			return rotateRight(root);
	}
	else {

		// in right subtree
		if (!root -> right) return root;

		if (k > root -> right -> key) { //right right

			root -> right -> right = splay(root -> right->right, k);
			root = rotateLeft(root); //first left rot
		}

		else if (k < root->right->key) { //right-left
			root -> right -> left = splay(root -> right -> left, k);
			if (root->right->left)
				root->right = rotateRight(root->right);
		}

		if (root -> right == NULL)
			return root;
		return rotateLeft(root);

	}

}

int find(void * d, int k) {
	//returns value if present else -1
	d -> root = splay(d -> root, k);
	if (root -> key != k)
		return -1;
	return root->value;
}