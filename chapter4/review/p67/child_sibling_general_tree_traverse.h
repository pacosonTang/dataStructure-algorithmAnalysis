#include <stdio.h>
#include <malloc.h>

#define ElementType char
#define ERROR(str) printf(str)

// you know every node is treated as a tree.
struct Tree;
typedef struct Tree* Tree;

struct Tree
{
	Tree child;
	Tree sibling;
	ElementType value;
};

Tree createTree();
void insertTree(Tree root, Tree t);
void printPreorder(Tree root, int);
void printPostorder(Tree root, int);

// create Tree with value e.
Tree createTree(ElementType e)
{
	Tree root = (Tree)malloc(sizeof(struct Tree));
	if(root==NULL)
	{
		ERROR("error:failed createTree().");		
	}
	else
	{
		root->value = e;
		root->child = NULL;
		root->sibling = NULL;

	}
	return root;
}

// insert t as a child into root.
void insertTree(Tree root, Tree t)
{
	Tree rootcopy = root;
	if(root==NULL)
	{
		ERROR("error: failed insertTree for root is NULL");
		return ;
	}
	if(root->child == NULL)
	{
		root->child = t;		
	}
	else
	{
		rootcopy = root->child;
		while(rootcopy->sibling)
		{
			rootcopy = rootcopy->sibling;
		}
		rootcopy->sibling = t;	
	}			
}

// traverse the tree in preorder.
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
		printPreorder(root->child, depth+1);
		printPreorder(root->sibling, depth);
	}
} 

// traverse the tree in postorder.
void printPostorder(Tree root, int depth)
{	
	int i = 0;
	
	if(root!=NULL)
	{
		printPostorder(root->child, depth+1);	 
		for(;i<depth;i++)
		{
			printf("    ");
		}
		printf("%c\n", root->value);	
		printPostorder(root->sibling, depth);	
	}
}

