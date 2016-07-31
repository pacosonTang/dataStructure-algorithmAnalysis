#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define ERROR(str) printf(str)

struct Tree;
typedef struct Tree* Tree;

struct Tree
{
	Tree left;
	Tree right;
	ElementType value;
};

Tree createTree(ElementType e);
Tree insertTree(Tree root, ElementType e);
void printPreorder(Tree root, int depth);
Tree makeEmpty(Tree tree);
Tree find(Tree root, ElementType e);
Tree findMin(Tree root);
Tree findMax(Tree root);
Tree deleteTree(Tree root, ElementType e);

// create a binary Tree with value e.
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
		root->left = NULL;
		root->right = NULL;

	}
	return root;
}

// insert t as a child into root.
Tree insertTree(Tree root, ElementType e)
{	
	if(root == NULL) //
	{
		root = createTree(e);
		if(root)
		{
			return root;
		}
		else 
		{
			return NULL;
		}
	}
	if(e > root->value)  // the tree node with value e inserting into right child of the parent 
	{
		root->right = insertTree(root->right, e);
	}
	else if(e < root->value)  // the tree node withe value e inserting into left child of the parent 		
	{
		root->left = insertTree(root->left, e);
	}
	else
	{
		ERROR(" you cannot insert the node into the tree for its value equals to one in the tree");
	}

	return root; // dont't forget this line !
}

// free all of nodes in the tree.
Tree makeEmpty(Tree tree)
{
	if(tree!=NULL)
	{
		makeEmpty(tree->left);
		makeEmpty(tree->right);
		free(tree);
	}
	return NULL;
}

// find the Tree node whose value equals to e.
Tree find(Tree root, ElementType e)
{
	if(root == NULL) // judge whether root is NULL or not
	{
		return NULL;
	}
	if(e > root->value)
	{
		return find(root->right, e);
	}
	else if(e < root->value)
	{
		return find(root->left, e);
	}
	else 
	{
		return root;
	}	
}

// find the minimum node in the tree.
// it is not adapted to using recursion.
Tree findMin(Tree root)
{
	if(root==NULL)
	{
		return NULL;
	}
	while(root->left != NULL)
	{
		root = root->left;
	}
	return root;	
}

// find the maximum node in the tree.
// it is not adapted to using recursion.
Tree findMax(Tree root)
{
	if(root==NULL)
	{
		return NULL;
	}
	while(root->right != NULL)
	{
		root = root->right;
	}
	return root;
}

// delete the node as the value equals to e.
Tree deleteTree(Tree root, ElementType e)
{
	Tree temp;

	if(root==NULL)
	{
		ERROR("elements not found, from func deleteTree.");
		return NULL;
	}
	
	if(e > root->value) 
	{
		root->right = deleteTree(root->right, e);
	}
	else if(e < root->value) 
	{
		root->left = deleteTree(root->left, e);
	}
	else // the value of root equals given e
	{
		if(root->left && root->right) // if the deleting node has both left and right
		{
			root->value = findMin(root->right)->value; // set root's value as the minimum of right tree of root
			root->right = deleteTree(root->right, root->value);			
		}		
		else  // one or zero child is not NULL
		{
			// root->left = deleteTree(root->left, root->value);	
			if(root->right != NULL) // if root->right doesn't equal to NULL
			{
				temp = root;
				root = root->right;
				free(temp);												
			}
			else if(root->left != NULL) // if root->left doesn't equal to NULL
			{
				temp = root;
				root = root->left;
				free(temp);				
			}
			else  // if both root->left and root->right equal to NULL
			{
				free(root);
				root = NULL;
			}
		}		
	}	
	return root;
}

// traverse the bianry Tree in preorder.
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
		printf("%d\n", root->value);
		printPreorder(root->left, depth+1);
		printPreorder(root->right, depth+1);
	}
} 