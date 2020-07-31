/* Floyd-Warshall Algroithm V0.1

   Copyright (C) 2020 Embecosm Limited <www.embecosm.com>
   Contributor: Mary Bennett <mary.bennett@embecosm.com>
   SPDX-License-Identifier: GPL-3.0-or-later */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* define v & dist */
#define VERTEX 4 /* Amount of nodes */
#define INFINITE 100000000 /* Max value for distances */
signed int DIST[VERTEX][VERTEX]; /* Grid of minimum distances */
#define LINE_LEN 60 /* Maximum line length of csv */
enum colour_t { BLACK, RED }; /* RB tree colour of nodes */

/* Structure for each distance */
typedef struct distances
{
  char *source;
  char *destination;
  int distance;
  int srcNode;
  int destNode;

  struct distances *next;
} DISTANCE;

/* Structure for a node */
typedef struct rb_node
{
  int key;               /* Node name */
  enum colour_t colour;   /* Colour property */
  char *str;              /* Node name (from csv) */

  struct rb_node *left;
  struct rb_node *right;
  struct rb_node *parent;
} RB_NODE;

DISTANCE *head = NULL;
DISTANCE *tail = NULL;
RB_NODE *root = NULL;

/* Usage info */
void usage (void);

/* Initialises board to -1 and sets diagonal */
void initBoard (void);

/* Work out how many collumns
   Return collumn length (FAIL: 0) */
unsigned int readFile (char fname[256]);

/* Adds a record to linked list */
/* Returns pass/fail */
int insertRecord (char *source, char *destination, const char *chDistance);

/* Deletes a linked list */
void delList (void);

/* Removes the last item in a linked list */
int delItem (void);

/* The meaty loop */
void loopDist (void);

/* Print dist */
void printDist (void);

/* Displays the list */
void displayList (void);

/* Reads linked list and assigns the distances to DIST */
void assignDist (void);

/* -----------------------
  Red black tree functions
  ------------------------ */

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
RB_NODE *insert (RB_NODE *n);

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

/* Creates new node from record */
RB_NODE *createRBNode (char *strRecord);

/* Sets keys */
/* From left to right of the tree, increment i */
/* Max number of nodes will be the right most key */
int setKeys (RB_NODE *root, int lastKey);


/* -----------------------
        Functions
  ------------------------ */

int main (int argc, char const *argv[])
{
  /* Load in CSV of distances */
  if (argc == 1)
    {
      usage();
      return 0;
    }
  else if (argc != 2)
    {
      printf("Please specify the CSV file as an input.\n");
      return -1;
    }
  char fname[256];
  strcpy(fname, argv[1]);

  int collumn = readFile(fname);
  if (collumn < 1)
    printf("ERROR: Wrong number of collumns.\n");
  //displayList();

  /* Find keys */
  int maxV = setKeys (root, 1);
  if (maxV == -1)
    {
      printf("ERROR: keys failed to set.\n");
      return -1;
    }
  else if (maxV != VERTEX + 1)
    {/* TODO: variable number of nodes */
      printf("ERROR: Wrong number of nodes.\n");
      return -1;
    }
  //displayTree (root);

  initBoard();

  /* Fill the easy squares */
  assignDist();

  printf("Current table:\n");
  printDist();

  loopDist();
  printf("\n\nNew table:\n");
  printDist();
  
  delList();

  printf("\n\n");

  return 0;
}

/* Usage info */
void usage (void)
{
  printf("Usage:\n");
  printf("Floyd Warshall Algortim Version 0.1\n\n");
  printf("Copyright (C) 2020 Embecosm Limited <www.embecosm.com>\n");
  printf("Contributor: Mary Bennett <mary.bennett@embecosm.com>\n");
  printf("SPDX-License-Identifier: GPL-3.0-or-later\n\n");
  printf("To run the program, please use './floyd text.csv' where text.csv is your csv file.\n\n");
  return;
}

/* Initialises board to -1 and sets diagonal */
void initBoard (void)
{
  /* Initialise to -1? */
  for (int m = 0; m < VERTEX; m++)
    for (int n = 0; n < VERTEX; n++)
      DIST[n][m] = INFINITE;

  /* Set the 0s */
  for (int i = 0; i < VERTEX; i++)
    DIST[i][i] = 0;
}

/* The meaty loop */
void loopDist (void)
{
  /*for k from 1 to V
  for i from 1 to V
    for j from 1 to V
      if dist[i][j] > dist[i][k] + dist[k][j]
      dist[i][j] <- dist[i][k] + dist[k][j]*/

  for (int k = 0; k < VERTEX; k++)
    for (int j = 0; j < VERTEX; j++)
      for (int i = 0; i < VERTEX; i++)
	{
	  if ((DIST[i][k] == INFINITE) || (DIST[k][j] == INFINITE)) {}
	  else if ((DIST[i][j] == INFINITE) || (DIST[i][j] > DIST[i][k] + DIST[k][j]))
	    DIST[i][j] = DIST[i][k] + DIST[k][j];
	}
}

/* Print dist */
void printDist (void)
{
  printf("|---------------|\n|");
  for (int i = 0; i < VERTEX; i++)
    {
      for (int j = 0; j < VERTEX; j++)
	{
	  printf(" %i |", DIST[i][j]);
	}
      printf("\n|---------------|\n|");
    }
}

/* Work out how many collumns
   Return collumn length (FAIL: 0) */
unsigned int readFile (char fname[256])
{
  FILE *file;
  file = fopen(fname, "r");
  if (file == NULL)
    {
      printf("ERROR: File not opening.\n");
      return -1;
    }

  int i = 0;

  char line[LINE_LEN];
  const char DELIM[3] = " ,";
  
  while (fgets (line, LINE_LEN, file) != NULL)
    {
      if (i != 0)
	{  
	  char *sour = strtok (line, DELIM);
	  if (sour == NULL)
	    {
	      printf("ERROR: source is NULL\n");
	      return 0;
	    }
	    
	  char *dest = strtok (NULL, DELIM);
	  if (dest == NULL)
	    {
	      printf("ERROR: destination is NULL\n");
	      return 0;
	    }
      	  char *dista = strtok (NULL, DELIM);
	  if (dista == NULL)
	    {
	      printf("ERROR: distance is NULL\n");
	      return 0;
	    }
	  
      	  if (insertRecord (sour, dest, dista) == -1)
	    return 0;  /* Fail */
	  }

      i++; //Gives amount of collumns
    }
  
  fclose(file);
  return i;
}

/* ---------------------
   Linked list functions
   --------------------- */

/* Displays the list */
void displayList (void)
{
  DISTANCE *record = head;
  while (record != NULL)
    {
      record = record->next;
    }
}

/* Adds a record to linked list */
/* Returns pass/fail */
int insertRecord (char* source, char* destination, const char *chDistance)
{
  DISTANCE *record = (DISTANCE *) malloc (sizeof (DISTANCE));
  record->next = NULL;

  /* Check if any are NULL */
  if (source == NULL || destination == NULL || chDistance == NULL)
    {
      printf("ERROR: not enough rows. From %s to %s is %s. \n", source, destination, chDistance);
      return -1;
    }
  
  /* Fill the record */
  record->source = strdup(source);
  record->destination = strdup(destination);
  int d = atoi (chDistance);
  if (d != 0)
    record->distance = d;
  else
    return -1;
  
  /* Check if it exists, if not add to tree */
   if ((record->srcNode = existNode (root, record->source)) == -1)
     root = insert (createRBNode (record->source));
   if ((record->srcNode = existNode (root, record->destination)) == -1)
     root = insert (createRBNode (record->destination));
     
  /* If list is blank */
  if (head == NULL)
    {
      head = record;
      tail = head;
      return 0;
    }
  /*Otherwise */
  if (tail == NULL){
    printf("ERROR: tail\n");
    return -1;}
  
  tail->next = record;
  tail = tail->next;

  return 0;
}

/* Deletes a linked list */
void delList (void)
{
  while (head != NULL)
    {
      signed int m = delItem();
      if (m == 1 || m == -1)
	return;
    }
}

/* Removes the last item in a linked list */
/* Return 1 if head removed */
int delItem (void)
{
  /* If no list, do nothing */
  if (head == NULL)
    return 1;
  else if (head->next != NULL)
    {
      DISTANCE *item = head;
      /* Go to the end of the list */
      while (item->next->next != NULL)
	{
	  item = item->next;
	}
      free (item->next);
      item->next = NULL;
      tail = item;
      return 0;
    }
  else /* Only HEAD exists */
    {
      free (head);
      return 1;
    }
  printf("ERROR: did not hit return\n");
  return -1;
}

/* Reads linked list and assigns the distances to DIST */
void assignDist (void)
{
  DISTANCE *record = head;
  while (record != NULL)
    {
      int x = existNode (root, record->source);
      int y = existNode (root, record->destination);

      if (x == -1 || y == -1)
	{
	  printf("ERROR: Key lookup failed (assignDist).\n");
	  return;
	}

      DIST [x - 1][y - 1] = record->distance;
      record = record->next;
    }
}


/* -----------------------
  Red black tree functions
  ------------------------ */

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
RB_NODE *insert (RB_NODE *n)
{
  if (n == NULL)
    {
      printf("WARNING: new node is null");
      return root;
    }

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
    if (strcasecmp (root->str, n->str) < 0)
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
  n->key = 0; /* Default */
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

  printf("(%s: %d) ", root->str, root->key);

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

/* Creates new node from record */
RB_NODE *createRBNode (char *strRecord)
{
  RB_NODE *newRB = (RB_NODE *)malloc (sizeof (RB_NODE));
  newRB->key = 0;
  newRB->str = strdup (strRecord);

  return newRB;
}

/* Sets keys */
/* From left to right of the tree, increment i */
/* Max number of nodes will be the right most key */
int setKeys (RB_NODE *root, int lastKey)
{
  /* If tree is empty */
  if (root == NULL)
    return -1;

  if (root->left != NULL)
    lastKey = setKeys (root->left, lastKey);

  root->key = lastKey++;
  
  if (root->right != NULL)
    lastKey = setKeys (root->right, lastKey);
  
  return lastKey;
}
