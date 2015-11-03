#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct BinaryHeap;
typedef struct BinaryHeap *BinaryHeap;

BinaryHeap initBinaryHeap(int capacity);
void insert(ElementType value, BinaryHeap bh);
ElementType deleteMin(BinaryHeap);
int isFull(BinaryHeap bh);
int isEmpty(BinaryHeap bh);
void printBinaryHeap(BinaryHeap bh);

struct BinaryHeap 
{
	int capacity;
	int size;	
	ElementType *elements;		
};