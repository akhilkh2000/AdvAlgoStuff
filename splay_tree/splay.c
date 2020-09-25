#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int key;
	int value;
	struct node* left;
	struct node* right;
	struct node* parent;

} node;

typedef struct dict {
	node* root;
} dict;

//this line was used in test code for statistics
//int count = 0;


node* new_node(int k , int v) {
	node* newNode = malloc(sizeof(node));
	//malloc fail
	if (newNode == NULL)
		return newNode;

	newNode -> key = k;
	newNode -> value = v;
	newNode -> left = NULL;
	newNode ->right = NULL;
	newNode ->parent = NULL;
	return newNode;

}

void* make_new_dictionary() {
	dict * d = malloc(sizeof(dict));
	if (d == NULL) {
		return NULL;
	}
	d -> root = NULL;
	return d;
}

void rotateLeft(dict*d, node* x) {
	//count++;
	node* temp = x -> right;
	//left child of temp becomes right child of x
	x-> right = temp ->left;

	//also now temp's parent becomes x
	temp -> parent = x -> parent;

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
}

void rotateRight(dict* d, node* x) {
	//count++;
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

}




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
		//printf("HEAP IS FULL ERROR IN CREATING NODE!");
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
	 
	 
	// printf("\n Preorder: ");
	// preorder(D, D->root);
	// printf("\n Inorder: ");
	// inorder(D, D->root);


}

// void inorder(dict* d, node* r) {
// 	if (r) {
// 		inorder(d, r->left);
// 		printf("%d\t", r->key);
// 		inorder(d, r -> right);
// 	}
// }

// void preorder(dict*d, node*r) {
// 	if (r) {
// 		printf("%d\t", r->key);
// 		preorder(d, r -> left);
// 		preorder(d, r->right);

// 	}
// }




//following lines are for personal testing and not part of submission
//int getCount() {
//	return count;
//}
// int main() {

// 	dict* d = make_new_dictionary();

// 	//node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
// 	insert(d, 15, 10);
// 	printf("root %d\n", d->root->key);
// 	insert(d, 10, 20);
// 	printf("root %d\n", d->root->key);
// 	insert(d, 17, 30);
// 	printf("root %d\n", d->root->key);
// 	insert(d, 7, 100);
// 	printf("root %d\n", d->root->key);
// 	insert(d, 13, 90);
// 	printf("root %d\n", d->root->key);
// 	insert(d, 16, 40);
// 	// insert(d, 50, 50);
// 	// insert(d, 60, 60);
// 	// insert(d, 70, 70);
// 	// insert(d, 80, 80);
// 	// insert(d, 150, 150);
// 	// insert(d, 110, 110);
// 	// insert(d, 120, 120);

// 	printf("%d\n", find(d, 10));
// 	printf("%d\n", find(d, 7));
// 	printf("%d\n", find(d, 16));
// 	printf("%d\n", find(d, 67));
// 	printf("%d\n", find(d, 17));

// 	inorder(d, d->root);

// 	printf("\npreoder\n");
// 	preorder(d, d->root);




// }


