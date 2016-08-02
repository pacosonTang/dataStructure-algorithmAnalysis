#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("error: %s", str)

struct TreeNode;
typedef struct TreeNode* TreeNode;
typedef struct TreeNode* LeftistHeap;
struct TreeNode
{
	ElementType value;
	TreeNode left;
	TreeNode right;
	int nullPathLen;
};

TreeNode createTreeNode(ElementType value);
LeftistHeap insert(LeftistHeap heap, ElementType value);
LeftistHeap merge(LeftistHeap h1, LeftistHeap h2); 
LeftistHeap secondMerge(LeftistHeap h1, LeftistHeap h2);
void printPreorder(int depth, TreeNode root);
LeftistHeap deleteMin(LeftistHeap heap);

// create tree node with value.
TreeNode createTreeNode(ElementType value)
{
	TreeNode temp = (TreeNode)malloc(sizeof(struct TreeNode));
	
	if(temp==NULL)
	{
		Error("failed createTreeNode() for out of space.");
		return NULL;		
	}
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;
	temp->nullPathLen = 0;

	return temp;
}

// insert value into the leftist heap.
LeftistHeap insert(LeftistHeap heap, ElementType value)
{
	TreeNode temp = createTreeNode(value);
	
	if(temp==NULL)
	{
		Error("failed insert().");
		return NULL;
	}
	else
	{
		return merge(heap, temp);
	}
}

// by default, h1->root->value > h2->root->value.
// merge h1 and h2.
LeftistHeap merge(LeftistHeap h1, LeftistHeap h2)
{
	
	if(h1==NULL) 
	{
		return h2;
	}
	else if(h2==NULL)
	{
		return h1;
	}

	if(h1->value < h2->value)
	{
		return secondMerge(h1, h2);
	}
	else if(h1->value > h2->value)
	{
		return secondMerge(h2, h1);
	}
	else
	{
		Error("failed merge() for the value has been inserted.");
		return h1;
	}
}

void swapChild(LeftistHeap h1)
{
	TreeNode temp;

	temp = h1->left;
	h1->left = h1->right;
	h1->right = temp;
}

// by default, h1->root->value > h2->root->value.
// second merge h1 and h2.
LeftistHeap secondMerge(LeftistHeap h1, LeftistHeap h2)
{
	if(h1->left==NULL) // if h1 has no left child.
	{
		h1->left = h2;
	}
	else // if h1 has a left child, then merge its right child with h2.
	{
		h1->right = merge(h1->right, h2);
	
		// after merging, dont forget to update the nullPathLen.
		if(h1->left->nullPathLen < h1->right->nullPathLen)
		{
			swapChild(h1);
		}
		h1->nullPathLen = h1->right->nullPathLen + 1;
		// update over.
	}
	return h1;
}

// delete minimal tree node from heap.
LeftistHeap deleteMin(LeftistHeap heap)
{
	LeftistHeap left;
	LeftistHeap right;

	if(heap==NULL)
	{
		Error("failed deleteMin() for the heap is NULL.");
		return heap;
	}
	
	left = heap->left;
	right = heap->right;
	free(heap);
	return merge(left, right);
}

// analog print directories and files name in the BinaryTree, which involves postorder traversal. 
void printPreorder(int depth, LeftistHeap root)
{           
    int i;

    if(root) 
	{      
        for(i = 0; i < depth; i++)
            printf("    ");     
        printf("%d\n", root->value);
        printPreorder(depth + 1, root->left); 
		 // Attention: there's difference between traversing binary tree and common tree.
        printPreorder(depth + 1, root->right);
    }
    else 
	{
        for(i = 0; i < depth; i++)
            printf("    ");     
        printf("NULL\n");
    }
}