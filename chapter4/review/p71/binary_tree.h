#include <stdio.h>
#include <malloc.h>

#define TreeElementType char
#define ERROR(str) printf(str)

struct Tree;
typedef struct Tree* Tree;

struct Tree
{
	Tree left;
	Tree right;
	TreeElementType value;
};

Tree createTree(TreeElementType e);
void insertTree(Tree root, Tree t, int);
void printPreorder(Tree root, int depth);

// create a binary tree with value e.
Tree createTree(TreeElementType e)
{
	Tree root = (Tree)malloc(sizeof(struct Tree));
	if(root==NULL)
	{
		ERROR("error:failed createTree().");		
	}
	else
	{
		root->value = e;
		root->left = NULL;
		root->right = NULL;

	}
	return root;
}

// insert t as a child into root. flag=0 means t as a left child otherwise a right one.
void insertTree(Tree root, Tree t, int flag)
{	
	if(root==NULL)
	{
		ERROR("error: failed insertTree for root is NULL");
		return ;
	}
	if(flag==0 && root->left == NULL)
	{
		root->left = t;		
	}
	else if(flag==1 && root->right == NULL)
	{
		root->right = t;
	}
	else 
	{
		ERROR("error: failed insertTree() for there is invalid space.");
	}
}
 
// traverse the bianry tree in preorder.
void printPreorder(Tree root, int depth)
{	
	int i = 0;

	for(;i<depth;i++)
	{
		printf("    ");
	}	
	if(root==NULL)
	{
		printf("NULL\n");
	}
	else if(root != NULL) 
	{		
		printf("%c\n", root->value);
		printPreorder(root->left, depth+1);
		printPreorder(root->right, depth+1);
	}
} 