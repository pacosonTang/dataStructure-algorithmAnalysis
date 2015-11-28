#include <stdio.h>
#include <malloc.h>
#include "huffman.h"

#define ElementType Tree
#define ElementTypePtr TreePtr

#define Error(str) printf("\n error: %s \n",str)   

struct BinaryHeap;
typedef struct BinaryHeap BinaryHeap;
typedef struct BinaryHeap* BinaryHeapPtr;

void initElement(ElementTypePtr temp);
ElementTypePtr buildElement();
void swap(ElementTypePtr x, ElementTypePtr y);
BinaryHeapPtr initBinaryHeap(int capacity);
void insertHeap(ElementType value, BinaryHeapPtr bh);
ElementTypePtr deleteMin(BinaryHeapPtr);
int isFull(BinaryHeapPtr bh);
int isEmpty(BinaryHeapPtr bh);
void percolateUp(int index, ElementTypePtr bh);
void percolateDownFromOne(int index, BinaryHeapPtr bh);
void printBinaryHeap(BinaryHeapPtr bh);
void printBinaryHeapFromZero(BinaryHeapPtr bh);

struct BinaryHeap 
{
	int capacity;
	int size;	
	ElementTypePtr *elements;		
};

BinaryHeapPtr bh;