#include "binaryheap.h"

//judge whether the BinaryHeap is full or not , also 1 or 0 
int isFull(BinaryHeap bh)
{
	return bh->size == bh->capacity - 1 ? 1 : 0 ;
}

//judge whether the BinaryHeap is empty or not , also 1 or 0 
int isEmpty(BinaryHeap bh)
{
	return bh->size == 0 ? 1 : 0 ;
}

void swap(ElementType *x, ElementType *y)
{
	ElementType temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

// get the left child of node under index with startup 1
int leftChildFromOne(int index)
{
	return index * 2;
}

ElementType deleteMin(BinaryHeap bh)
{	
	ElementType minimum;
	ElementType *data;	
		
	if(isEmpty(bh))
	{
		Error("failed deleting minimum , for the BinaryHeap is empty, from func deleteMin !");
		return -1;	
	}

	data = bh->elements;	
	minimum = data[1];

	swap(&data[1], &data[bh->size]);
	bh->size-- ; // size-- occurs prior to percolateDownFromOne 
	percolateDownFromOne(1, bh) ;	

	return minimum;
} 

// Attention, the index of the heap starts from 1
void insert(ElementType value, BinaryHeap bh)
{
	int i;

	if(isFull(bh))
	{
		Error("failed insertion , for the BinaryHeap is full, from func insert!");
		return ;	
	}

	for(i = ++bh->size; bh->elements[i/2] > value; i /= 2)
		bh->elements[i] = bh->elements[i / 2];

	bh->elements[i] = value;
}

BinaryHeap initBinaryHeap(int capacity)
{
	BinaryHeap bh;
	ElementType *temp;

	bh = (BinaryHeap)malloc(sizeof(struct BinaryHeap));
	if(!bh) {
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    }  
	bh->capacity = capacity;
	bh->size = 0;

	temp = (ElementType *)malloc(capacity * sizeof(ElementType));
	if(!temp) {
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    } 
	bh->elements = temp;

	return bh;
}

void printBinaryHeap(BinaryHeap bh)
{
	int i;
	ElementType *temp;
	
	if(!bh)
		Error("printing execution failure, for binary heap is null, from func printBinaryHeap");	

	temp = bh->elements;
	for(i = 1; i < bh->capacity; i++)
	{
		printf("\n\t index[%d] = ", i);
		if(i <= bh->size)
			printf("%d", bh->elements[i]);
		else
			printf("NULL");
	}
	printf("\n");
}  

//print the binary heap who starts from index 0
void printBinaryHeapFromZero(BinaryHeap bh)
{
	int i;
	ElementType *temp;
	
	if(!bh)
		Error("printing execution failure, for binary heap is null, from func printBinaryHeap");	

	temp = bh->elements;
	for(i = 0; i < bh->capacity; i++)
	{
		printf("\n\t index[%d] = ", i);
		if(i < bh->size)
			printf("%d", bh->elements[i]);
		else
			printf("NULL");
	}
	printf("\n");
}  
