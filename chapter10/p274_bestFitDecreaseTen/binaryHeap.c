#include "binaryheap.h"

#define maxKey 20

// allocate memory to build new element
ElementTypePtr buildElement()
{
	ElementTypePtr temp;		

	temp = (ElementTypePtr)malloc(sizeof(ElementType));
	if(!temp)
	{
		Error("failed buildElement, for out of space");
		return NULL;
	}
	temp->next = NULL;

	return temp;
}

//judge whether the BinaryHeap is full or not , also 1 or 0 
int isFull(BinaryHeapPtr bh)
{
	return bh->size == bh->capacity - 1 ? 1 : 0 ;
}

//judge whether the BinaryHeap is empty or not , also 1 or 0 
int isEmpty(BinaryHeapPtr bh)
{
	return bh->size == 0 ? 1 : 0 ;
}

// Attention, the index of the heap starts from 1
void insertHeap(ElementType value, BinaryHeapPtr bh)
{
	int i;

	if(isFull(bh))
	{
		Error("failed insertion , for the BinaryHeap is full, from func insert!");
		return ;	
	}

	for(i = ++bh->size; bh->elements[i/2]->key < value.key; i /= 2)
		*bh->elements[i] = *bh->elements[i / 2];

	*bh->elements[i] = value;
}

// initialize the binary heap with capacity
BinaryHeapPtr initBinaryHeap(int capacity)
{
	BinaryHeapPtr temp;
	int i;

	temp = (BinaryHeapPtr)malloc(sizeof(BinaryHeap));
	if(!temp)
	{
		Error("failed initBinaryHeap, for out of space");
		return NULL;
	}

	temp->elements = (ElementTypePtr*)malloc(sizeof(ElementTypePtr));
	if(!temp->elements)
	{
		Error("failed initBinaryHeap, for out of space");
		return NULL;
	}
	temp->size = 0;
	temp->capacity = capacity;

	for(i=0; i<capacity; i++)	
		temp->elements[i] = buildElement();	 
	
	temp->elements[0]->key = maxKey;
	return temp;
	
}

void swap(ElementTypePtr x, ElementTypePtr y)
{
	ElementType temp;

	temp = *x;
	*x = *y;
	*y = temp;
}
 
// get the parent of the element with index 
int parentFromOne(int index)
{
	return index / 2;
}

// percolating up the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateUpFromOne(int index, BinaryHeapPtr bh)
 {	
	ElementTypePtr *data;
	ElementTypePtr temp;
	int size;	
	int parent;
		
	data = bh->elements;
	size = bh->size;
	
	for(temp = data[index]; parentFromOne(index) > 0; index = parent)
	{
		parent = parentFromOne(index);
		if(parent == 0 || temp->key > data[parent]->key)
			break;
		else		
			data[index] = data[parent];					 						
	}
	data[index] = temp;
 }
 
 // get the left child of node under index with startup one
int leftChildFromOne(int index)
{
	return index * 2;
}
 
// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateDownFromOne(int index, BinaryHeapPtr bh)
 {	
	ElementTypePtr *data;
	int size;
	ElementTypePtr temp;
	int child;

	data = bh->elements;
	size = bh->size;

	for(temp = data[index]; leftChildFromOne(index) <= size; index = child)
	{
		child = leftChildFromOne(index);
		if(child < size && data[child]->key < data[child+1]->key)
			child++;
		if(temp->key < data[child]->key)
			data[index] = data[child];
		else
			break;
	}
	data[index] = temp;
 }   
 
ElementTypePtr deleteMin(BinaryHeapPtr bh)
{	
	ElementTypePtr minimum;
	ElementTypePtr *data;	
		
	minimum = buildElement();
	if(isEmpty(bh))
	{
		Error("failed deleting minimum , for the BinaryHeap is empty, from func deleteMin !");
		return NULL;
	}

	data = bh->elements;	
	*minimum = *data[1];

	swap(data[1], data[bh->size]);
	bh->size-- ; // size-- occurs prior to percolateDownFromOne 
	percolateDownFromOne(1, bh) ;	

	return minimum;
} 

void printBinaryHeap(BinaryHeapPtr bh)
{
	int i;
	ElementTypePtr* temp;
	
	if(isEmpty(bh))
		Error("printing execution failure, for binary heap is null, from func printBinaryHeap");	

	temp = bh->elements;
	printf("\n=== the binary heap we built just now is as follows: ===\n");
	for(i = 1; i < bh->capacity; i++)
	{
		printf("\n\t heap[%d] = ", i);
		if(i <= bh->size)
			printf("key[%d]", bh->elements[i]->key);
		else
			printf("NULL"); 
	}
	printf("\n");
} 