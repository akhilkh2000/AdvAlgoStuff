#include <stdio.h>
#include <stdlib.h>
// #include "splay_tree_imp.h"

typedef struct word
{
  int key;
  int val;
  struct word *left;
  struct word *right;
  struct word *parent;
} word;

typedef struct dictionary
{
  struct word *root;
} dictionary;

word *new_word(int key, int val)
{
  word *n = malloc(sizeof(word));
  n->key = key;
  n->val = val;
  n->parent = NULL;
  n->right = NULL;
  n->left = NULL;

  return n;
}

void *make_new_dictionary()
{
  dictionary *t = malloc(sizeof(dictionary));
  t->root = NULL;

  return t;
}

word *maximum(dictionary *t, word *x)
{
  while (x->right != NULL)
    x = x->right;
  return x;
}

void left_rotate(dictionary *t, word *x)
{
  word *y = x->right;
  x->right = y->left;
  if (y->left != NULL)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL)
  { //x is root
    t->root = y;
  }
  else if (x == x->parent->left)
  { //x is left child
    x->parent->left = y;
  }
  else
  { //x is right child
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void right_rotate(dictionary *t, word *x)
{
  word *y = x->left;
  x->left = y->right;
  if (y->right != NULL)
  {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL)
  { //x is root
    t->root = y;
  }
  else if (x == x->parent->right)
  { //x is left child
    x->parent->right = y;
  }
  else
  { //x is right child
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void splay(dictionary *t, word *n)
{
  while (n->parent != NULL)
  { //word is not root
    if (n->parent == t->root)
    { //word is child of root, one rotation
      if (n == n->parent->left)
      {
        right_rotate(t, n->parent);
      }
      else
      {
        left_rotate(t, n->parent);
      }
    }
    else
    {
      word *p = n->parent;
      word *g = p->parent; //grandparent

      if (n->parent->left == n && p->parent->left == p)
      { //both are left children
        right_rotate(t, g);
        right_rotate(t, p);
      }
      else if (n->parent->right == n && p->parent->right == p)
      { //both are right children
        left_rotate(t, g);
        left_rotate(t, p);
      }
      else if (n->parent->right == n && p->parent->left == p)
      {
        left_rotate(t, p);
        right_rotate(t, g);
      }
      else if (n->parent->left == n && p->parent->right == p)
      {
        right_rotate(t, p);
        left_rotate(t, g);
      }
    }
  }
}

/*

word *search(dictionary *t, word *n, int x)
{
  if (x == n->key)
  {
    splay(t, n);
    return n;
  }
  else if (x < n->key)
    return search(t, n->left, x);
  else if (x > n->key)
    return search(t, n->right, x);
  else
    return NULL;
}

int find(void *t, int key)
{
  dictionary *ptr_t = t;
  word *root = ptr_t->root;
  word *check = search(ptr_t, root, key);
  if (check)
    return check->key;
  return -1;
}

*/

int find_helper(dictionary *t, word *node, int data)
{
  if (!node)
    return -1;
  else if (node->key == data)
  {
    splay(t, node);
    return data;
  }
  else if (node->key > data)
    return find_helper(t, node->left, data);
  return find_helper(t, node->right, data);
}

int find(void *t, int key)
{
  dictionary *ptr_t = t;
  word *root = ptr_t->root;
  return find_helper(ptr_t, root, key);
}

void insert_helper(dictionary *t, word *n)
{
  word *y = NULL;
  word *temp = t->root;
  while (temp != NULL)
  {
    y = temp;
    if (n->key == temp->key)
    {
      temp->val = n->val;
      return;
    }
    if (n->key < temp->key)
      temp = temp->left;
    else
      temp = temp->right;
  }
  n->parent = y;

  if (y == NULL) //newly added word is root
    t->root = n;
  else if (n->key < y->key)
    y->left = n;
  else
    y->right = n;

  splay(t, n);
}

void insert(void *t, int key, int val)
{
  dictionary *ptr_t = t;
  word *temp = new_word(key, val);
  insert_helper(ptr_t, temp);
}

// void delete (dictionary *t, word *n)
// {
//   splay(t, n);

//   dictionary *left_subtree = make_new_dictionary();
//   left_subtree->root = t->root->left;
//   if (left_subtree->root != NULL)
//     left_subtree->root->parent = NULL;

//   dictionary *right_subtree = make_new_dictionary();
//   right_subtree->root = t->root->right;
//   if (right_subtree->root != NULL)
//     right_subtree->root->parent = NULL;

//   free(n);

//   if (left_subtree->root != NULL)
//   {
//     word *m = maximum(left_subtree, left_subtree->root);
//     splay(left_subtree, m);
//     left_subtree->root->right = right_subtree->root;
//     t->root = left_subtree->root;
//   }
//   else
//   {
//     t->root = right_subtree->root;
//   }
// }

void inorder(dictionary *t, word *n)
{
  if (n != NULL)
  {
    inorder(t, n->left);
    printf("%d and %d\n", n->key, n->val);
    inorder(t, n->right);
  }
}

int main()
{
  dictionary *t = make_new_dictionary();

  insert(t, 10, 100);
  printf("%d is the root now\n", t->root->key);
  insert(t, 20, 200);
  printf("%d is the root now\n", t->root->key);
  insert(t, 30, 300);
  printf("%d is the root now\n", t->root->key);
  insert(t, 40, 400);
  printf("%d is the root now\n", t->root->key);
  insert(t, 50, 500);
  printf("%d is the root now\n", t->root->key);
  insert(t, 60, 600);
  printf("%d is the root now\n", t->root->key);

  // inorder(t, t->root);
  printf("find function now\n");
  int check = find(t, 30);
  printf("%d is the root now\n", t->root->key);
  printf("%d is the check\n", check);

  // inorder(t, t->root);

  return 0;
}