#include "top.h"

BinaryHeap initBinaryHeap(int capacity);
void insert(ElementType value, BinaryHeap bh);
ElementType deleteMin(BinaryHeap);
void printBinaryHeap(BinaryHeap bh);
int isEmpty(BinaryHeap bh); 

void swap(ElementType *x, ElementType *y);
int leftChild(int index);
int isFull(BinaryHeap bh);
void percolateUp(int index, BinaryHeap bh);
void percolateDown(int index, BinaryHeap bh);


// judge whether the BinaryHeap is full or not , also 1 or 0 .
// you should know the element under index 0 don't store any content.
int isFull(BinaryHeap bh)
{
	return bh->size == bh->capacity - 1 ? 1 : 0 ;
}

// judge whether the BinaryHeap is empty or not , also 1 or 0 
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
int leftChild(int index)
{
	return index*2;
}

// initialize binary heap with given capacity.
BinaryHeap initBinaryHeap(int capacity)
{
	BinaryHeap bh;
	ElementType *temp;

	bh = (BinaryHeap)malloc(sizeof(struct BinaryHeap));
	if(!bh) 
	{
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    }  
	bh->capacity = capacity;
	bh->size = 0;

	temp = (ElementType *)malloc(capacity * sizeof(ElementType));
	if(!temp) 
	{
        Error("out of space, from func initBinaryHeap");        
        return NULL;
    } 
	bh->array = temp;
	// bh->array[0] = INT_MIN; // 小根堆.
	bh->array[0] = INT_MAX; // 大根堆.

	return bh;
}

// Attention, the index of the heap starts from 1
// insert the value into binary heap based on percolateUp().
void insert(ElementType value, BinaryHeap bh)
{	
	if(isFull(bh))
	{
		Error("failed insertion , for the BinaryHeap is full, from func insert!");
		return ;	
	}
	bh->array[++bh->size] = value; // startup is 1 not 0.
	percolateUp(bh->size, bh);
}

 // percolating up the element when its value is greater than children (minimal heap)
 //Attention: all of bh->array starts from index 1
void percolateUp(int i, BinaryHeap bh)
{	
	ElementType temp = bh->array[i];
	
	for(; temp > bh->array[i/2]; i/=2)
	{
		bh->array[i] = bh->array[i/2];
	}
	bh->array[i] = temp;
}

// delete minimal from binary heap based on percolateDown().
ElementType deleteMin(BinaryHeap bh)
{		
	ElementType *data = bh->array;		

	swap(&data[1], &data[bh->size]); // &variable means nickname of the variable
	bh->size-- ; // size-- occurs prior to percolateDown(). 
	percolateDown(1, bh) ;	

	return data[bh->size+1];
} 

// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->array starts from index 1
 void percolateDown(int index, BinaryHeap bh)
 {  
    ElementType *data = bh->array;
    int size = bh->size;
    ElementType temp;
    int child;
        
	// for循环的 leftChild(index) <= size 必须要取 等号.
    for(temp = data[index]; leftChild(index) <= size; index = child)
    {
        child = leftChild(index);
        if(child < size && data[child] < data[child+1]) // if 语句里的 child < size 不取等号.
		{
            child++;
		}
        if(temp < data[child])
		{
            data[index] = data[child];
		}
		else
		{
            break;
		}
    }
    data[index] = temp; 
 }

// print binary heap.
void printBinaryHeap(BinaryHeap bh)
{
	int i;
	ElementType *array;
	
	if(!bh)
	{
		Error("printing execution failure, for binary heap is null, from func printBinaryHeap");	
		return; 
	}

	array = bh->array;
	for(i=1; i <= bh->size; i++)
	{
		printf("\n\t index[%d] = ", i);				
		printf("%d", array[i]);
	}
	printf("\n");
}  
