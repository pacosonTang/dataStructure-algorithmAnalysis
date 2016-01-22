#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str) 

struct TreeNode;
typedef struct TreeNode* TreeNode;
typedef TreeNode BinominalTree;

struct TreeNode
{
	ElementType value;
	TreeNode leftChild;
	TreeNode nextSibling;		
};
 
struct BinominalQueue;
typedef struct BinominalQueue* BinominalQueue;
struct BinominalQueue
{	
	int capacity;
	BinominalTree* trees;
};

BinominalQueue init(int);
void insert(ElementType, BinominalQueue);
void deleteMin(BinominalQueue);

void outerMerge(BinominalQueue bq1, BinominalQueue bq2);
BinominalTree merge(BinominalTree h1, int height, BinominalQueue bq);
BinominalTree innerMerge(BinominalTree h1, int height, BinominalTree h2, BinominalQueue bq);
int minimal(BinominalQueue);
