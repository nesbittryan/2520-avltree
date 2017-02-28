#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct node {
  char * key;
  int count;
  int height;
  struct node * left;
  struct node * right;
};

struct head {
	struct node * node;
};

typedef struct node Node;
typedef struct head Head;     

/*
* FUNC:	frees a node one node at a time. Doesnt free keyValues because
		not all are neccessarily stored in memory. Also we arent being marked
		on free-ing so i used this just to slightly clear up space
* IN:	root (node *)
* OUT:	nothing (void)
*/
void freeTree(Node * node);

/*
* FUNC:	builds the head for the tree using
        the input file
* IN:	char * filename
* OUT:	head *(tree head)
*/
Head * initializeTree(char * filename);

/*
* FUNC:	removes a node to a tree, incremenating count down
        if exists or removing if count = 1
* IN:	node *
* OUT:	node *
*/
Node * removeNode(Node * node, char * key);

/*
* FUNC:	adds a node to a tree, incremenating count if
        it exists or adding it to the tree
* IN:	node *
* OUT:	node *
*/
Node * addNode(Node * node, char * key);

/*
* FUNC:	balances the tree by checking
        heights of each nodes children
        and performing the right techniques
        to re balance it
* IN:	node *
* OUT:	node *
*/
Node * balance(Node * node);

/*
* FUNC:	performs a left rotation
* IN:	node *
* OUT:	node *
*/
Node * rotateLeft(Node * node);

/*
* FUNC:	performs a right rotation
* IN:	node *
* OUT:	node *
*/
Node * rotateRight(Node * node);

/*
* FUNC:	performs a double left rotation, which is
        equivalent to node->right right rotation and then
        a left rotation
* IN:	node *
* OUT:	node *
*/
Node * rotateDoubleLeft(Node * node);

/*
* FUNC:	performs a double right rotation, which is
        equivalent to node->left left rotation and then
        a right rotation
* IN:	node *
* OUT:	node *
*/
Node * rotateDoubleRight(Node * node);

/*
* FUNC:	removes the lowest node from the tree
* IN:	node *
* OUT:	lowest node
*/
Node* removeLowest(Node * node);

/*
* FUNC:	finds the lowest node down from a given node
* IN:	node *
* OUT:	lowest node
*/
Node * findLowest(Node * node);

/*
* FUNC:	tests if the node is external (true), or if internal (false)
* IN:	the node to test (node *)
* OUT:	int 1 if external, 0 if internal
*/
int isExternal(Node * n);


int searchTree(Node * node, char * key);

/*
* FUNC:	gets the size of the tree by adding every non-NULl node
* IN:	root (node *)
* OUT:	returns height of tree (int)
*/
int size(Node * node);

/*
* FUNC:	gets the height of tree by finding longest chain from node
* IN:	root (node *)
* OUT:	returns height of tree (int)
*/
int height(Node * node);

/*
* FUNC:	displays the key if it is found, returns 0 if no key exists
* IN:	root (node *), key to find
* OUT:	int 1 if found, 0 if not
*/
int displayKey(Node * node, char * key);

/*
* FUNC:	traverses the whole tree and prints every key and count above
        a desired count
* IN:	root (node *), int count to compare to
* OUT: void, prints to screen
*/
void printKeyAboveCount(Node * node, int count);
