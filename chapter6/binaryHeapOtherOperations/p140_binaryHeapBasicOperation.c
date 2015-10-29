#include "binaryheap.h"

extern void percolateUp(int index, BinaryHeap bh);

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

ElementType deleteMin(BinaryHeap bh)
{
	ElementType minimal;
	ElementType lastElement;
	int size;
	int i;	

	if(isEmpty(bh))
	{
		Error("failed deleting minimum , for the BinaryHeap is empty, from func deleteMin !");
		return -1;	
	}

	minimal = bh->elements[1];
	lastElement = bh->elements[bh->size]; // for the index of last element is greater than the size , so the last one should be moved
	i = 1;
	size = bh->size;
	
	while(1) // there are 3 cases that the last one moving up has double, single or no children
	{
		if(2*i >= size)
			break;
		i = bh->elements[2*i] < bh->elements[2*i+1] ? 2*i : 2*i+1 ;         
		bh->elements[i/2] = bh->elements[i];
	}			
	
	bh->elements[i] = lastElement;			
	bh->size--;
	percolateUp(i, bh);
	
	return minimal;
}

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

