#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int key;
	int value;
	struct node* left, *right, *parent;
} node;

typedef struct dict {
	node* root;
} dict;



node* new_node(int k , int v) {
	node* newNode = malloc(sizeof(node));
	newNode -> key = k;
	newNode -> value = v;
	newNode -> left = NULL;
	newNode ->right = NULL;
	newNode ->parent = NULL;
	return newNode;

}

void* make_new_dictionary() {
	dict * d = malloc(sizeof(dict));
	d -> root = NULL;
	return d;
}

node*rotateLeft(dict*d, node* x) {
	node* temp = x -> right;
	//left child of temp becomes right child of x
	x-> right = temp ->left;

	//also now temp's parent becomes x
	temp -> parent = x;

	//if x has no parent initially
	if (x -> parent == NULL) {
		//x is root so now temp takes it's place
		d -> root = temp;
	}
	else if (x == x -> parent-> left) {
		x -> parent -> left = temp;
	}
	else {
		x -> parent ->right = temp;
	}

	//if temp had a child
	if (temp -> left) {
		//  x becomes its new parent
		temp -> left -> parent = x;
	}



	temp -> left =  x;
	x -> parent = temp;
	return temp;
}

node*rotateRight(dict* d, node* x) {
	node* temp = x -> left;
	//right child of temp becomes left child of x
	x->left = temp->right;

	//also now temps parent becomes x's original parent
	temp -> parent = x -> parent;

	//if x has no parent
	if (x -> parent == NULL) {
		// x is root
		d-> root = temp;
	}
	else if (x == x->parent->left) {
		//x is left child of parent
		x -> parent -> left = temp;
	}
	else {
		//x is right child
		x -> parent -> right = temp;
	}

	if (temp -> right) {
		//if it has a right child it becomes left child of x
		temp -> right -> parent = x;
	}


	//this comes to root position and its right child becomes x
	temp -> right  =  x;
	x -> parent = temp;
	return  temp;

}

// node* splay(node* root, int k) {
// 	if (!root || root ->key == NULL)
// 		return root;
// 	if (k < root->key) {
// 		//left subtree
// 		if (!root -> left) return root;

// 		//left-left
// 		if (k < root->left->key) {
// 			//recursively splay till key comes to root->left->left
// 			root->left->left = splay(root->left->left, k);
// 			//do one right rotation
// 			root = rotateRight(root);

// 		}
// 		else if (k > root->left->key) { //left - right
// 			root -> left -> right = splay(root -> left ->right, k);
// 			if (root ->left -> right)
// 				root -> left = rotateLeft(root->left);

// 		}

// 		if (root -> left == NULL) return root; //only one rotation
// 		else
// 			//second rotation
// 			return rotateRight(root);
// 	}
// 	else {

// 		// in right subtree
// 		if (!root -> right) return root;

// 		if (k > root -> right -> key) { //right right

// 			root -> right -> right = splay(root -> right->right, k);
// 			root = rotateLeft(root); //first left rot
// 		}

// 		else if (k < root->right->key) { //right-left
// 			root -> right -> left = splay(root -> right -> left, k);
// 			if (root->right->left)
// 				root->right = rotateRight(root->right);
// 		}

// 		if (root -> right == NULL)
// 			return root;
// 		return rotateLeft(root);

// 	}

// }


void splay(void* d, node* n) {

	dict* D = (dict*)d;

	//till n becomes root
	while (n -> parent != NULL) {

		//parent is root node (zig left or zig right)
		if (n -> parent == D -> root) {
			if (n == n -> parent -> left)
				rotateRight(D, n->parent);
			else
				rotateLeft(D, n->parent);
		}

		else {
			node*parent = n->parent;
			node*grandParent = n->parent->parent;

			//now 4 cases

			//following 2 are zig-zig
			// both are left children
			if (n == parent ->left && parent == grandParent -> left) {
				//two right rotations
				rotateRight(D, grandParent);
				rotateRight(D, parent);
			}

			else if (n == parent ->right && parent == grandParent -> right) {
				//two left rotations
				rotateLeft(D, grandParent);
				rotateLeft(D, parent);
			}

			//following 2 are zig-zag type
			else if (n == parent -> left && parent == grandParent -> right) {

				//rotate right on parent then left rotation on gp
				rotateRight(D, parent);
				rotateLeft(D, grandParent);
			}

			else {
				rotateLeft(D, parent);
				rotateRight(D, grandParent);
			}
		}
	}


}
int find(void * d, int k) {
	//returns value if present else -1
	dict* D = (dict*)d;
	node* root =  D -> root;
	while (root) {
		if (root -> key == k) {
			splay(d, root);
			return root -> value;
		}
		else if (k < root -> key)
			root = root -> left;
		else
			root = root -> right;
	}

	return -1;
}

void insert(void* d, int key, int value) {
	dict* D = (dict*)d;
	node* newNode = new_node(key, value);
	if (!newNode) {
		printf("HEAP IS FULL ERROR IN CREATING NODE!");
		exit(1);
	}

	//nodes made so that actual addresses are not modified / lost
	node* root = D-> root;
	node* temp = NULL;
	while (root) {
		temp = root;
		if (key < root -> key)
			root = root -> left;
		else if (key  > root -> key)
			root =  root-> right;
		else {
			//node already exists
			//cahnge value and splay it
			root -> value = value;
			splay(D, root);
			free(newNode);
			return;
		}

	}

	newNode -> parent = temp; //we had stored earlier
	if (temp == NULL) {
		// this is the first node in the splay tree
		D -> root = newNode;
	}

	else if (key < temp -> key) {
		// new Node is left child
		temp ->left = newNode;
	}

	else //right child
		temp -> right = newNode;

	//now splay this new node to the top
	splay(D, newNode);


}