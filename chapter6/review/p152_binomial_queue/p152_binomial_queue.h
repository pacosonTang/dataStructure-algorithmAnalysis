#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define ElementType int
#define Error(str) printf("error: %s", str)

struct TreeNode;
typedef struct TreeNode* TreeNode;
struct TreeNode
{
	ElementType value;
	TreeNode child;
	TreeNode sibling;
};

struct BinomialQueue;
typedef struct BinomialQueue* BinomialQueue;
struct BinomialQueue
{
	int capacity;
	TreeNode* array;
};

BinomialQueue init(int capacity);
TreeNode createTreeNode(ElementType value);
void insert(BinomialQueue queue, ElementType value);
void merge(BinomialQueue queue, TreeNode node, int height);
void printBinomialQueue(BinomialQueue bq);
TreeNode mergeSameTree(TreeNode node1, TreeNode node2);
void deleteMin(BinomialQueue queue);

// init binominal queue with capacity.
BinomialQueue init(int capacity)
{
	int i;
	BinomialQueue queue = (BinomialQueue)malloc(sizeof(struct BinomialQueue));

	if(queue==NULL)
	{
		Error("failed init() for out of space.");
		return queue;
	}
	queue->capacity = capacity;
	
	queue->array = (TreeNode*)malloc(sizeof(TreeNode)*capacity);
	if(queue->array==NULL)
	{
		Error("failed init() for out of space.");
		return NULL;
	}

	for(i=0; i<capacity; i++)
	{
		queue->array[i] = NULL;		
	}
	return queue;
}

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
	temp->child = NULL;
	temp->sibling = NULL;

	return temp;
}

// insert the node with value into the queue.
void insert(BinomialQueue queue, ElementType value)
{
	TreeNode temp = createTreeNode(value);

	if(temp==NULL)
	{
		return ;
	}	
	merge(queue, temp, 0);	// inserting is the special case of merging operation.
}

// merge queue and node under height.
void merge(BinomialQueue queue, TreeNode node, int height)
{
	if(height >= queue->capacity) // if height is greater than queue->capacity
	{
		Error("failed merge() for height is greater than queue's capacity.");
		return;
	}
	if(queue->array[height]==NULL) // if the queue doesnt has the node under given height.
	{
		queue->array[height] = node;
	}
	else
	{
		queue->array[height] = mergeSameTree(queue->array[height], node); // 对同height的二项树进行merge.
		while(queue->array[height+1]!=NULL) // 融合后, height 自增1, (height+1)高度下是否有二项树.
		{
			node = queue->array[height];
			queue->array[height] = NULL; // 暂存 queue->array[height] 后，将其置空.
			height++;
			if(height >= queue->capacity) // if height is greater than queue->capacity
			{
				Error("failed merge() for height is greater than queue's capacity.");
				return;
			}
			queue->array[height] = mergeSameTree(queue->array[height], node);
		}
		queue->array[height+1] = queue->array[height];
		queue->array[height] = NULL;
	}		
}

// return the last child by sibling pointer.
TreeNode lastChild(TreeNode root)
{				
	while(root->sibling)
	{		
		root = root->sibling;
	}
	return root; 
}

// by default, node1->value is less than node2->value.
// merge trees with same size.
TreeNode mergeSameTree(TreeNode node1, TreeNode node2)
{
	if(node1->value > node2->value)
	{
		return mergeSameTree(node2, node1);
	}
	if(node1->child==NULL) // if node1 has no child.
	{
		node1->child = node2;
	}
	else // node1 has 1 or multiple children.
	{
		lastChild(node1->child)->sibling = node2;
	}
	return node1;
} 

// analog print node values in the binominal tree, which involves preorder traversal. 
void printPreorderChildSibling(TreeNode root, int depth)
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
		printPreorderChildSibling(root->child, depth+1);
		printPreorderChildSibling(root->sibling, depth);
	}
}

// print Binominal Queue bq
void printBinomialQueue(BinomialQueue bq)
{
	int i;

	for(i=0; i<bq->capacity; i++)
	{
		printf("bq[%d] = \n", i);
		printPreorderChildSibling(bq->array[i], 1);
	}	
}

// delete minimal from queue.
void deleteMin(BinomialQueue queue)
{	
	int i, min_height, height;
	ElementType value = INT_MAX;
	TreeNode temp, sibling;

	for(i=0; i<queue->capacity; i++)
	{
		if(queue->array[i]!=NULL)
		{
			if(queue->array[i]->value < value)
			{
				min_height = i;
				value = queue->array[i]->value;
			}
		}
	}
	
	temp = queue->array[min_height]->child;
	free(queue->array[min_height]);
	queue->array[min_height] = NULL; // 这里务必要置空, 其兄弟为NULL时 才表示 森林分离为多个二项树.
	height = 0;

	while(temp)
	{
		sibling = temp->sibling;
		temp->sibling = NULL;
		merge(queue, temp, height++);		
		temp = sibling;
	}	
}