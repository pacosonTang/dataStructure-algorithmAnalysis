#include "binaryHeapMax.h"
#include <math.h>

extern char flag[];

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

// get the left child of node under index with startup 1
int leftChildFromOne(int index)
{
	return index * 2;
} 

void swap(ElementTypePtr x, ElementTypePtr y)
{
	ElementType temp;
	
	temp = *x;
	*x = *y;
	*y = temp;	
}

ElementType deleteMax(BinaryHeap bh)
{	
	ElementType maximum;
	ElementTypePtr *data;	
	
	if(isEmpty(bh))
	{
		Error("failed deleting minimum , for the BinaryHeap is empty, from func deleteMax !");
		maximum.vertex = -1;
		maximum.reverse = -1;
		return maximum;
	}
	data = bh->elements;	 
	maximum = *data[1];
		
	swap(data[1], data[bh->size]);		
	bh->size-- ; // size-- occurs prior to percolateDownFromOne 
	percolateDownFromOne(1, bh) ;
	
	return maximum;
} 

// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateDownFromOne(int index, BinaryHeap bh)
 {	
	ElementTypePtr *data;	
	ElementType temp;
	int size;
	int child;

	data = bh->elements;
	size = bh->size;	

	for(temp = *data[index]; leftChildFromOne(index) <= size; index = child)
	{
		child = leftChildFromOne(index);
		if(child < size && data[child]->reverse < data[child+1]->reverse)
			child++;
		if(temp.reverse < data[child]->reverse)
		{			
			*data[index] = *data[child];			
		}
		else
			break;
	}	
	*data[index] = temp;		
 }
// create heap node
 ElementTypePtr makeHeapNode()
 {
	ElementTypePtr temp;

	temp = (ElementTypePtr)malloc(sizeof(ElementType));
	if(!temp)
	{
		Error("out of space, from func makeHeapNode");        
		return NULL;
	}
	return temp;
 }
// Attention, the index of the heap starts from 1
// return the index the element inserted into the binary heap
void insertHeap(ElementTypePtr value, BinaryHeap bh)
{
	int i;
	
	if(isFull(bh))
	{
		Error("failed insertion , for the BinaryHeap is full, from func insert!");
		return ;	
	}	
	if(!isEmpty(bh))
	{
		for(i = ++bh->size; bh->elements[i/2]->reverse < value->reverse; i /= 2)		 			
		{
			//copyElement(bh->elements[i/2], bh->elements[i]);		 
			*bh->elements[i] = *bh->elements[i/2];		
		}
	}
	else
		i = ++bh->size;		
	*bh->elements[i] = *value;	
}

BinaryHeap initBinaryHeap(int capacity)
{
	BinaryHeap bh;
	ElementTypePtr *temp;
	int i;

	bh = (BinaryHeap)malloc(sizeof(struct BinaryHeap));
	if(!bh) {
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    }  
	bh->capacity = capacity;
	bh->size = 0;

	temp = (ElementTypePtr*)malloc(capacity * sizeof(ElementTypePtr));
	if(!temp) {
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    } 
	bh->elements = temp;
	
	for(i=0; i < capacity; i++)
	{
		temp[i] = (ElementTypePtr)malloc(sizeof(ElementType));
		if(!temp[i]) {
			Error("out of space, from func initBinaryHeap");        
			return NULL;
		} 		
	}
	bh->elements[0]->reverse = MaxInt;
	return bh;
}

// allocate the memory for storing index of  vertex in heap and let every element -1
int *makeEmptyArray(int size)
{
	int *array;
	int i;

	array = (int*)malloc(size * sizeof(int));
	if(!array)
	{
		Error("out of space ,from func makeEmptyArray");
		return NULL;
	}		
	for(i=0; i<size; i++)
		array[i] = -1;

	return array;
}  

void printBinaryHeap(BinaryHeap bh)
{
	int i;
	ElementTypePtr *temp;
	
	if(!bh)
		Error("printing execution failure, for binary heap is null, from func printBinaryHeap");	

	temp = bh->elements;
	for(i = 1; i < bh->capacity; i++)
	{
		printf("\n\t heap[%d]: ", i);
		if(i <= bh->size)
			printf("reverse[%c] = %d", flag[bh->elements[i]->vertex], bh->elements[i]->reverse+1);		
		else
			printf("NULL");
	}
	printf("\n");	
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
	reverse tempDisStruct;
	int *indexOfVertexInHeap;
	
	printf("\n\t=== test for inserting the binary heap with {85, 80, 40, 30, 10, 70, 110} in turn ===\n");
	capacity = 14;
	bh = initBinaryHeap(capacity);
	size = 7;	
	
	tempDisStruct = makeEmptyreverse(); 
	indexOfVertexInHeap = makeEmptyArray(size);

	for(i = 0; i < size; i++) 
	{
		tempDisStruct->reverse = data[i];
		tempDisStruct->vertexIndex = i;
		insert(tempDisStruct, bh, indexOfVertexInHeap);
	}	
	printBinaryHeap(bh);
	printIndexOfVertexInHeap(bh->size, indexOfVertexInHeap);

	printf("\n\t=== test for inserting the binary heap with element {100, 20, 90} in turn ===\n");
	
	tempDisStruct->reverse = 100;
	tempDisStruct->vertexIndex = size;
	insert(tempDisStruct, bh, indexOfVertexInHeap);	
	printBinaryHeap(bh);

	tempDisStruct->reverse = 20;
	tempDisStruct->vertexIndex = size+1;
	insert(tempDisStruct, bh, indexOfVertexInHeap);	
	printBinaryHeap(bh);

	tempDisStruct->reverse = 90;
	tempDisStruct->vertexIndex = size+2;
	insert(tempDisStruct, bh, indexOfVertexInHeap);	
	printBinaryHeap(bh);

	printIndexOfVertexInHeap(bh->size, indexOfVertexInHeap);

	printf("\n\t=== test for inserting the binary heap with 5 ===\n");	
	tempDisStruct->reverse = 5;
	tempDisStruct->vertexIndex = size+3;
	insert(tempDisStruct, bh, indexOfVertexInHeap);	
	printBinaryHeap(bh);

	printf("\n\t=== test for 3 deletings towards the minimum in binary heap ===\n");
	deleteMin(bh, indexOfVertexInHeap);	
	printBinaryHeap(bh);
	deleteMin(bh, indexOfVertexInHeap);		
	printBinaryHeap(bh);
	deleteMin(bh, indexOfVertexInHeap);	
	printBinaryHeap(bh);
}
*/
