#include <stdio.h>
#include <malloc.h>
#include "distance.h"

#define ElementType Distance

#define Error(str) printf("\n error: %s \n",str)   

struct BinaryHeap;
typedef struct BinaryHeap *BinaryHeap;

void swap(ElementType *x, ElementType *y);
BinaryHeap initBinaryHeap(int capacity);
void insert(ElementType value, BinaryHeap bh);
ElementType deleteMin(BinaryHeap);
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
	ElementType *elements;		
};