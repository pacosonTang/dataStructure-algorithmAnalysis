#include <stdio.h>
#include <malloc.h>

#define Error(str) printf("\n\t error: %s\n", str)
 
struct Node;
typedef struct Node* Node;
typedef struct Node* TopDownSplayTree;

struct Node
{
	int value;
	Node left;
	Node right;
}; 

void printPreorder(int depth, TopDownSplayTree root);
TopDownSplayTree topdown_splay(int value, TopDownSplayTree);
Node makeNode(int);
TopDownSplayTree left_left_single_rotate(TopDownSplayTree);
TopDownSplayTree right_right_single_rotate(TopDownSplayTree);
TopDownSplayTree insert(int value, TopDownSplayTree root);
TopDownSplayTree deleteNode(int value, TopDownSplayTree root);
