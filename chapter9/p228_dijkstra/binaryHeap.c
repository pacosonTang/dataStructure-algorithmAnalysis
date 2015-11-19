#include "binaryheap.h"
#include <math.h>

#define MaxInt (int)pow(2, 16)
//judge whether the BinaryHeap is full or not , also 1 or 0 
int isFull(BinaryHeap bh)
{
	return bh->size == bh->capacity - 1;
}

//judge whether the BinaryHeap is empty or not , also 1 or 0 
int isEmpty(BinaryHeap bh)
{
	return bh->size == 0;
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
		return NULL;	
	}

	data = bh->elements;	
	minimum = data[1];

	swap(&data[1], &data[bh->size]);
	bh->size-- ; // size-- occurs prior to percolateDownFromOne 
	percolateDownFromOne(1, bh) ;	

	return minimum;
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
		printf("\n\t heap[%d] = ", i);
		if(i <= bh->size)
			printf("vertex[%d] + distance[%d]", bh->elements[i]->vertexIndex+1, bh->elements[i]->distance);		
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
			printf("%d", bh->elements[i]->distance);
		else
			printf("NULL");
	}
	printf("\n");
}  

// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateDownFromOne(int index, BinaryHeap bh)
 {	
	ElementType *data;
	int size;
	ElementType temp;
	int child;

	data = bh->elements;
	size = bh->size;

	for(temp = data[index]; leftChildFromOne(index) <= size; index = child)
	{
		child = leftChildFromOne(index);
		if(child < size && data[child]->distance > data[child+1]->distance)
			child++;
		if(temp->distance > data[child]->distance)
			data[index] = data[child];
		else
			break;
	}
	data[index] = temp;
 }

//copy vertexIndex and distance from 'from' to 'to'
void copyElement(ElementType from, ElementType to)
{
	to->vertexIndex = from->vertexIndex;
	to->distance = from->distance;
}

// Attention, the index of the heap starts from 1
// return the index the element inserted into the binary heap
void insert(ElementType value, BinaryHeap bh, int* heapIndexRecord)
{
	int i;
	
	if(isFull(bh))
	{
		Error("failed insertion , for the BinaryHeap is full, from func insert!");
		return ;	
	}	
	if(!isEmpty(bh))
		for(i = ++bh->size; bh->elements[i/2]->distance > value->distance; i /= 2)		 			
		{
			copyElement(bh->elements[i/2], bh->elements[i]);		 
			heapIndexRecord[bh->elements[i]->vertexIndex] = i; //update the heapIndexRecord
		}
	else
		i = ++bh->size;	
	copyElement(value, bh->elements[i]);		 	
	heapIndexRecord[bh->elements[i]->vertexIndex] = i; //update the heapIndexRecord
}

BinaryHeap initBinaryHeap(int capacity)
{
	BinaryHeap bh;
	ElementType *temp;
	int i;

	bh = (BinaryHeap)malloc(sizeof(struct BinaryHeap));
	if(!bh) {
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    }  
	bh->capacity = capacity;
	bh->size = 0;

	temp = (ElementType*)malloc(capacity * sizeof(Distance));
	if(!temp) {
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    } 
	bh->elements = temp;
	
	for(i=0; i < capacity; i++)
	{
		temp[i] = (ElementType)malloc(sizeof(struct Distance));
		if(!temp[i]) {
			Error("out of space, from func initBinaryHeap");        
			return NULL;
		} 		
	}

	return bh;
}

 
/*
int main()
{
	int data[] = {85, 80, 40, 30, 10, 70, 110}; // P141	
	int buildHeapData[] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
	BinaryHeap bh;	
	int size;
	int i;	
	int capacity;
	Distance tempDisStruct;
	
	printf("\n\t=== test for inserting the binary heap with {85, 80, 40, 30, 10, 70, 110} in turn ===\n");
	capacity = 14;
	bh = initBinaryHeap(capacity);
	size = 7;	
	
	tempDisStruct = makeEmptyDistance(); 
	for(i = 0; i < size; i++) 
	{
		tempDisStruct->distance = data[i];
		tempDisStruct->vertexIndex = i;
		insert(tempDisStruct, bh);
	}
	printf("test");
	printBinaryHeap(bh);

	printf("\n\t=== test for inserting the binary heap with element {100, 20, 90} in turn ===\n");
	
	tempDisStruct->distance = 100;
	tempDisStruct->vertexIndex = size;
	insert(tempDisStruct, bh);	

	tempDisStruct->distance = 20;
	tempDisStruct->vertexIndex = size+1;
	insert(tempDisStruct, bh);	

	tempDisStruct->distance = 90;
	tempDisStruct->vertexIndex = size+2;
	insert(tempDisStruct, bh);	

	printBinaryHeap(bh);

	printf("\n\t=== test for inserting the binary heap with 5 ===\n");	
	tempDisStruct->distance = 5;
	tempDisStruct->vertexIndex = size+3;
	insert(tempDisStruct, bh);	
	printBinaryHeap(bh);

	printf("\n\t=== test for 3 deletings towards the minimum in binary heap ===\n");
	deleteMin(bh);	
	printBinaryHeap(bh);
	deleteMin(bh);		
	printBinaryHeap(bh);
	deleteMin(bh);	
	printBinaryHeap(bh);
}
*/