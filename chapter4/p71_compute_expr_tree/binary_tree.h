#include <stdio.h>
#include <malloc.h>

#define TreeElementType char
#define Error(str) printf("%s",str) 

struct BinaryTree;
typedef struct BinaryTree *BinaryTree;

BinaryTree createBinaryTree(TreeElementType); // this func is different from that in p70_preorder_binary_tree.c
BinaryTree makeTreeEmpty(BinaryTree);
BinaryTree insert(TreeElementType, BinaryTree, int);
BinaryTree insertNode(BinaryTree, BinaryTree, int);
BinaryTree find(TreeElementType, BinaryTree);
void printPostorder(int depth, BinaryTree root);

// we adopt child-sibling notation
struct BinaryTree
{
	TreeElementType value;
	BinaryTree left;
	BinaryTree right;
};
