// C program for Red-Black Tree insertion
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<assert.h>

enum colour_t { BLACK, RED };

/* Structure for a node */
typedef struct rb_node
{
  int key;
  enum colour_t colour;   /* Colour property */
  char *str;

  struct rb_node *left;
  struct rb_node *right;
  struct rb_node *parent;
} RB_NODE;


/* Gets parent of the node */
RB_NODE *getParent (RB_NODE *n);

/* Gets the sibling of the node */
RB_NODE *getSibling (RB_NODE *n);

/* Rotate left: Can updates the root of the tree */
void rotateLeft (RB_NODE *n);

/* Rotate right: Can updates the root of the tree */
void rotateRight (RB_NODE *n);

/* Insert new node */
/* Will call InsertRepairTree to fix the tree and return the new root */
RB_NODE *insert (RB_NODE *root, RB_NODE *n);

/* Insert new node n */
void insertNode (RB_NODE *root, RB_NODE *n);

/* Repairs the tree after a node is inserted */
void insertRepairTree (RB_NODE *n);

/* Part of repair when parent is red but uncle is black.
   Must rotate new node to grand parent position. */
void insertCase4 (RB_NODE *n);

/* Displays tree */
void displayTree (RB_NODE *root);

/* Deletes binary tree (normal BST delete function) */
void delTree (RB_NODE *root);

/* Checks if node exists */
/* Retruns true/ false */
int existNode (RB_NODE *root, char *str);

/* Sets keys */
/* From left to right of the tree, increment i */
void setKeys (RB_NODE *root, int lastKey);


int main()
{
  RB_NODE *root = NULL;
  RB_NODE *newN = (RB_NODE *) malloc (sizeof (RB_NODE)); // Need to remove
  newN->key = 10;
  newN->str = strdup ("hello");
  printf ("newN->key = %i, newN->str = %s\n", newN->key, newN->str);

  root = insert(root, newN);

  displayTree(root);

  int found = existNode(root, newN->str);
  if (found == -1)
    printf ("\nNODE NOT FOUND\n");
  else
    printf ("\nNode: %i", found);

  setKeys (root, 1);
  printf("\nNew tree:");
  displayTree(root);

  delTree(root);
  return 0;
}

/* Gets parent of the node */
RB_NODE *getParent (RB_NODE *n)
{
  return n == NULL ? NULL : n->parent;
}

/* Gets the sibling of the node */
RB_NODE *getSibling (RB_NODE *n)
{
  RB_NODE *p = getParent(n);

  /* If no parent, no sibling */
  if (p == NULL)
    return NULL;

  if (n == p->left)
    return p->right;
  else
    return p->left;
}

/* Rotate left: Can updates the root of the tree */
void rotateLeft (RB_NODE *n)
{
  /* If n does not exist, exit */
  if (!n || !n->right)
    return;

  RB_NODE *newNode = n->right;
  RB_NODE *p = getParent(n); /* Finds the parent */
  assert (newNode != NULL);  /* Cannot become internal if tree is empty (i.e if newNode is NULL) */

  n->right = newNode->left; /* Store newNode's left subtree as n's right child */
  newNode->left = n;
  n->parent = newNode;

  /* Handle other child/parent pointers */
  if (n->right != NULL)
  {
    n->right->parent = n;
  }

  /* If n's parent is not NULL */
  if (p != NULL)
  {
    if (n == p->left)
      p->left = newNode;
    else if (n == p->right)
      p->right = newNode;
  }
  /* If n's parent is NULL, can make newNode root */

  newNode->parent = p;
}

/* Rotate right: Can updates the root of the tree */
void rotateRight (RB_NODE *n)
{
  /* If n does not exist, exit */
  if (!n || !n->left)
    return;

  RB_NODE *newNode = n->left;
  RB_NODE *p = getParent(n); /* Finds the parent */
  assert (newNode != NULL);  /* Cannot become internal if tree is empty (i.e if newNode is NULL) */

  n->left = newNode->right; /* Store newNode's left subtree as n's right child */
  newNode->right = n;
  n->parent = newNode;

  /* Handle other child/parent pointers */
  if (n->right != NULL)
  {
    n->right->parent = n;
  }

  /* If n's parent is not NULL */
  if (p != NULL)
  {
    if (n == p->left)
      p->left = newNode;
    else if (n == p->right)
      p->right = newNode;
  }
  /* If n's parent is NULL, can make newNode root */

  newNode->parent = p;
}

/* Insert new node */
/* Will call InsertRepairTree to fix the tree and return the new root */
RB_NODE *insert (RB_NODE *root, RB_NODE *n)
{
  /* Insert new node */
  insertNode (root, n);

  /* Repair tree */
  insertRepairTree (n);

  /* Return new root */
  root = n;
  while (getParent(root) != NULL)
  {
    root = getParent(root);
  }
  return root;
}

/* Insert new node n */
void insertNode (RB_NODE *root, RB_NODE *n)
{
  /* Recusivly descend tree until leaf is found */
  /* If there is a tree */
  if (root != NULL)
  {
    if (n->key < root->key) /* Data compare */
    {
      if (root->left != NULL)
      {
        insertNode (root->left, n);
        return;
      }
      else
        root->left = n;
    }
    else
    {
      if (root->right != NULL)
      {
        insertNode (root->right, n);
        return;
      }
      else
        root->right = n;
    }
  }

  /* Fill in new node */
  n->parent = root;
  n->left = NULL;
  n->right = NULL;
  n->colour = RED;
}

/* Repairs the tree after a node is inserted */
void insertRepairTree (RB_NODE *n)
{
  if (getParent (n) == NULL)
    /* Case 1: current node is root, repaint black */
    n->colour = BLACK;
  else if (getParent(n)->colour == BLACK)
    /* Case 2: tree is valid */
    return;
  else if (getSibling (getParent (n)) != NULL && getSibling (getParent (n))->colour == RED)
  {
    /* Case 3: Both parent & uncle are red.
       Therefore both get repainted black & grandparent red.
       Grand parent may now break tree => tree is repaired */
    getParent(n)->colour = BLACK;
    getSibling(getParent(n))->colour = BLACK;
    getParent(getParent(n))->colour = RED;
    insertRepairTree(n);
  }
  else
    /* Case 4: Parent is red but uncle is black */
    insertCase4 (n);
}

/* Part of repair when parent is red but uncle is black.
   Must rotate new node to grand parent position. */
void insertCase4 (RB_NODE *n)
{
  RB_NODE *p = getParent (n);
  RB_NODE *g = getParent (p);

  /* Move new node to outside of subtree */
  if (n == p->right && p == g->left)
  {
    rotateLeft(p);
    n = n->left;
  }
  else if (n == p->left && p == g->right)
  {
    rotateRight (p);
    n = n->right;
  }

  /* P becomes the root with subtrees of new node and g */
  if (n == p->left)
    rotateRight(g);
  else
    rotateLeft(g);

  p->colour = BLACK;
  g->colour = RED;

  return;
}

/* Displays tree */
void displayTree (RB_NODE *root)
{
  /* If tree is empty */
  if (root == NULL)
  {
    return;
  }

  /* Recusivly find leaf */
  if (root->left != NULL)
    displayTree(root->left);

  printf("%d ", root->key);

  if (root->right != NULL)
    displayTree(root->right);
}

/* Deletes binary tree (normal BST delete function) */
void delTree (RB_NODE *root)
{
  /* If tree is empty */
  if (root == NULL)
    return;

  /* Recusivly find leaf */
  if (root->left != NULL)
    delTree (root->left);

  if (root->right != NULL)
    delTree (root->right);

  free (root);
}

/* Checks if node exists */
/* Retruns key/ false (-1) */
int existNode (RB_NODE *root, char *str)
{
  /* If no tree */
  if (root == NULL)
    return -1;

  /* If it is a match */
  if (strcasecmp (root->str, str) == 0)
    return root->key;

  /* If leaf */
  if (root->left == NULL && root->right == NULL)
    return -1;
  /* Recusivly search for node */
  else
  {
    if (root->left != NULL)
      return existNode (root->left, str);
    if (root->right != NULL)
      return existNode (root->right, str);
  }

  printf("ERROR: Reached end of existNode\n");
  return -1;
}

/* Sets keys */
/* From left to right of the tree, increment i */
/* Max number of nodes will be the right most key */
void setKeys (RB_NODE *root, int lastKey)
{
  /* If tree is empty */
  if (root == NULL)
    return;

  /* If leaf */
  if (root->left == NULL && root->right == NULL)
  {
    root->key = lastKey;
    lastKey++;
  }
  /* Recusivly search for node */
  else
  {
    if (root->left != NULL)
      setKeys (root->left, lastKey++);
    if (root->right != NULL)
      setKeys (root->right, lastKey++);
  }
}
