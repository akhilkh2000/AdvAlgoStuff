#include <stdio.h>
#include <stdlib.h>
#include "splay_tree_imp.h"

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
  //---------------------------------
  //long count;
  //---------------------------------
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
  //----------------------------------
  //t->count = 0;
  //----------------------------------

  return t;
}

word *maximum(dictionary *t, word *x)
{
  while (x->right != NULL)
    x = x->right;
  return x;
}

void ROTATION_LEFT(dictionary *t, word *x)
{

	//---------------------------------
	//t->count++;
	//---------------------------------
  word *y = x->right;
  x->right = y->left;
  if (y->left != NULL)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL)
  {
    //root
    t->root = y;
  }
  else if (x == x->parent->left)
  { //left child
    x->parent->left = y;
  }
  else
  { //right child
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void ROTATION_RIGHT(dictionary *t, word *x)
{
	//---------------------------------
	//t->count++;
	//---------------------------------
  word *y = x->left;
  x->left = y->right;
  if (y->right != NULL)
  {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL)
  { //root
    t->root = y;
  }
  else if (x == x->parent->right)
  { //left child
    x->parent->right = y;
  }
  else
  { //right child
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void MAKE_IT_ROOT(dictionary *t, word *n)
{
  while (n->parent != NULL)
  { //not root
    if (n->parent == t->root)
    { //child of root, one rotation
      if (n == n->parent->left)
      {
        ROTATION_RIGHT(t, n->parent);
      }
      else
      {
        ROTATION_LEFT(t, n->parent);
      }
    }
    else
    {
      word *p = n->parent;
      //grandparent
      word *g = p->parent;

      if (n->parent->left == n && p->parent->left == p)
      { //both left
        ROTATION_RIGHT(t, g);
        ROTATION_RIGHT(t, p);
      }
      else if (n->parent->right == n && p->parent->right == p)
      { //both right
        ROTATION_LEFT(t, g);
        ROTATION_LEFT(t, p);
      }
      else if (n->parent->right == n && p->parent->left == p)
      {
        ROTATION_LEFT(t, p);
        ROTATION_RIGHT(t, g);
      }
      else if (n->parent->left == n && p->parent->right == p)
      {
        ROTATION_RIGHT(t, p);
        ROTATION_LEFT(t, g);
      }
    }
  }
}

int find_helper(dictionary *t, word *node, int data)
{
  if (!node)
    return -1;
  else if (node->key == data)
  {
    MAKE_IT_ROOT(t, node);
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

  if (y == NULL)
    t->root = n;
  else if (n->key < y->key)
    y->left = n;
  else
    y->right = n;

  MAKE_IT_ROOT(t, n);
}

void insert(void *t, int key, int val)
{
  dictionary *ptr_t = t;
  word *temp = new_word(key, val);
  insert_helper(ptr_t, temp);
}

/*

long get_count(void** t) {
dictionary *ptr = *t;
return ptr->count;
}

*/



