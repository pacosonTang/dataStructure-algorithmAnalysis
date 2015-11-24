#include <stdio.h>
#include <malloc.h>
#include "reverseIndex.h"

#define ElementType ReverseIndex
#define ElementTypePtr ReverseIndexPtr

#define Error(str) printf("\n error: %s \n",str)   

struct BinaryHeap;
typedef struct BinaryHeap *BinaryHeap;

void swap(ElementTypePtr x, ElementTypePtr y);
BinaryHeap initBinaryHeap(int capacity);
ElementTypePtr makeHeapNode();
void insertHeap(ElementTypePtr value, BinaryHeap bh);
ElementType deleteMax(BinaryHeap);
int isFull(BinaryHeap bh);
int isEmpty(BinaryHeap bh);
void percolateUp(int index, BinaryHeap bh);
void percolateDownFromOne(int index, BinaryHeap bh);
void printBinaryHeap(BinaryHeap bh);
void printBinaryHeapFromZero(BinaryHeap bh);

struct BinaryHeap 
{
	int capacity;
	int size;	
	ElementTypePtr *elements;		
};