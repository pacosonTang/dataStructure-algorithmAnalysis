#include <stdio.h>
#include <malloc.h>

#define ElementType int
struct TreeNode;
#define Error(str) printf("\n error: %s \n",str) 
typedef struct TreeNode* TreeNode;
typedef struct TreeNode* PriorityQueue;

struct TreeNode
{
	ElementType value;
	TreeNode left;
	TreeNode right;	
};

PriorityQueue insert(ElementType, PriorityQueue);
PriorityQueue deleteMin(PriorityQueue);
void printPreorder(int depth, TreeNode root);
PriorityQueue merge(PriorityQueue, PriorityQueue);
PriorityQueue innerMerge(PriorityQueue h1, PriorityQueue h2);
void swap(PriorityQueue h1);
int minimal(int a, int b);
