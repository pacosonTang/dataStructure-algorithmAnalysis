#include "binominal_queue.h" 

#define MINIMAL 10000

int minimal(BinominalQueue bq)
{
	int capacity;
	int i;
	int minimal;
	int miniIndex;	

	minimal = MINIMAL;
	capacity = bq->capacity;
	for(i=0; i<capacity; i++)
	{
		if(bq->trees[i] && bq->trees[i]->value < minimal)
		{
			minimal = bq->trees[i]->value;
			miniIndex = i;
		}
	}

	return miniIndex;
}

// initialize the BinominalQueue with given capacity.
BinominalQueue init(int capacity)
{
	BinominalQueue queue;			
	BinominalTree* trees; 
	int i;

	queue = (BinominalQueue)malloc(sizeof(struct BinominalQueue));
	if(!queue)
	{
		Error("failed init, for out of space !");
		return queue;
	}	
	queue->capacity = capacity;
	
	trees = (BinominalTree*)malloc(capacity * sizeof(BinominalTree));
	if(!trees)
	{
		Error("failed init, for out of space !");
		return NULL;
	}	
	queue->trees = trees;

	for(i=0; i<capacity; i++)
	{
		queue->trees[i] = NULL;
	}
	
	return queue;
}  

// attention: the root must be the left child of the binominal tree.
int getHeight(BinominalTree root)
{
	int height;		
	if(root == NULL)
	{		
		return 0;		
	}

	height = 1;	
	while(root->nextSibling)
	{
		height++;
		root = root->nextSibling;
	}

	return height;
}


// merge BinominalQueue bq2 into bq1.
void outerMerge(BinominalQueue bq1, BinominalQueue bq2)
{
	int height;
	int i;

	for(i=0; i<bq2->capacity; i++)
	{
		height = -1;
		if(bq2->trees[i])
		{
			height = getHeight(bq2->trees[i]->leftChild);	
			// attention for the line above
			// height = height(bq2->trees[i]->leftChild); not height = height(bq2->trees[i]);
			merge(bq2->trees[i], height, bq1);
		}					
	}		
}

// merge tree h1 and h2 = bq->trees[height], 
// who represents the new tree and old one respectively.
BinominalTree merge(BinominalTree h1, int height, BinominalQueue bq)
{			
	if(h1 == NULL)
	{
		return h1;
	}

	if(bq->trees[height] == NULL) // if the queue don't has the B0 tree.
	{		
		bq->trees[height] = h1;
		return bq->trees[height];
	}
	else // otherwise, compare the new tree's height with that of old one.
	{		 
		if(h1->value > bq->trees[height]->value) // the new should be treated as the parent of the old.
		{		
			innerMerge(bq->trees[height], height, h1, bq);
		}
		else // the old should be treated as the parent of the new.
		{
			innerMerge(h1, height, bq->trees[height], bq);
		}
	}  

	return h1;
} 

BinominalTree lastChild(BinominalTree root)
{				
	while(root->nextSibling)
	{		
		root = root->nextSibling;
	}

	return root; 
}

// merge tree h1 and h2 = bq->trees[height], 
// who represents the new tree and old one respectively.
BinominalTree innerMerge(BinominalTree h1, int height, BinominalTree h2, BinominalQueue bq)
{
	if(h1->leftChild == NULL)
	{
		h1->leftChild = h2;
	}
	else
	{
		lastChild(h1->leftChild)->nextSibling = h2;
		// attention for the line above
		// lastChild(h1->leftChild)->nextSibling = h2 not lastChild(h1)->nextSibling = h2
	}
	height++;
	bq->trees[height-1] = NULL;
	merge(h1, height, bq);	
	
	return h1;
} 

// insert an element with value into the priority queue.
void insert(ElementType value, BinominalQueue bq)
{
	TreeNode node;

	node = (TreeNode)malloc(sizeof(struct TreeNode));
	if(!node)
	{
		Error("failed inserting, for out of space !");
		return ;
	}
	node->leftChild= NULL;
	node->nextSibling = NULL;	
	node->value = value;	
		
	merge(node, 0, bq);			
}

// analog print node values in the binominal tree, which involves preorder traversal. 
void printPreorderChildSibling(int depth, BinominalTree root)
{			
	int i;
	
	if(root) {		
		for(i = 0; i < depth; i++)
			printf("    ");
		printf("%d\n", root->value);			
		printPreorderChildSibling(depth + 1, root->leftChild);									
		printPreorderChildSibling(depth, root->nextSibling);
	} 
	else
	{
		for(i = 0; i < depth; i++)
			printf("    ");
		printf("NULL\n");
	}
}

// print Binominal Queue bq
void printBinominalQueue(BinominalQueue bq)
{
	int i;

	for(i=0; i<bq->capacity; i++)
	{
		printf("bq[%d] = \n", i);
		printPreorderChildSibling(1, bq->trees[i]);
	}	
}

int main()
{
	BinominalQueue bq, bq1, bq2;	
	int data[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int data1[] = {65, 24, 12, 51, 16, 18};	
	int data2[] = {24, 65, 51, 23, 14, 26, 13};
	int i;
	int capacity;	

	// creating the binominal queue bq starts.
	capacity = 7;
	bq = init(capacity);		
	for(i=0; i<capacity; i++)
	{
		insert(data[i], bq);
	}
	printf("\n=== after the  binominal queue bq is created ===\n");	
	printBinominalQueue(bq);	
	// creating over.
	 
	// creating the binominal queue bq1 starts.
	capacity = 6;
	bq1 = init(capacity);		
	for(i=0; i<capacity; i++)
	{
		insert(data1[i], bq1);
	}
	printf("\n=== after the binominal queue bq1 is created ===\n");	
	printBinominalQueue(bq1);	
	// creating over.

	// creating the binominal queue bq2 starts.
	capacity = 7;
	bq2 = init(capacity);		
	for(i=0; i<capacity; i++)
	{
		insert(data2[i], bq2);
	}
	printf("\n=== after the binominal queue bq2 is created ===\n");	
	printBinominalQueue(bq2);	
	// creating over.	 

	// merge bq2 into the bq1 
	outerMerge(bq1, bq2);
 	printf("\n=== after bq2 is merged into the bq1 ===\n");	
	printBinominalQueue(bq1);	
	// merge over. 
	
	// executing deleteMin opeartion towards binominal queue bq1	
	printf("\n=== after executing deleteMin opeartion towards binominal queue bq1 ===\n");	
	deleteMin(bq1);	
	printBinominalQueue(bq1);	
	// deleteMin over!
	return  0;
}

void deleteMin(BinominalQueue bq)
{
	int i;	
	BinominalTree minitree;	
	BinominalTree sibling;

	i = minimal(bq);
	minitree = bq->trees[i]->leftChild; //minitree->value=51
	free(bq->trees[i]);
	bq->trees[i] = NULL;			

	while(minitree)
	{
		sibling = minitree->nextSibling;
		minitree->nextSibling = NULL;
		merge(minitree, getHeight(minitree->leftChild), bq);		
		minitree = sibling;
	}		
}
