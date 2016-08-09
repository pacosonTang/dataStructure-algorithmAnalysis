#include "top.h"

void swap(ElementType *x, ElementType *y);
int leftChild(int index);
BinaryHeap initBinaryHeap(int capacity);
void insert(ElementType value, BinaryHeap bh);
ElementType deleteMin(BinaryHeap);
int isFull(BinaryHeap bh);
int isEmpty(BinaryHeap bh);
void percolateUp(int index, BinaryHeap bh);
void percolateDown(int index, BinaryHeap bh);
void printBinaryHeap(BinaryHeap bh);

// index == 顶点编号, value == 顶点被访问的序号.
ElementType createHeapNode(int index, int value)
{
	struct HeapNode node;
	
	node.value = value;
	node.index = index;
	return node;
}

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
	// bh->array[0].value = INT_MIN; // 小根堆
	bh->array[0].value = INT_MAX; // 大根堆

	return bh;
}

// Attention, the index of the heap starts from 1
// insert the value into binary heap based on percolateUp().
void insert(ElementType e, BinaryHeap bh)
{		
	if(isFull(bh))
	{
		Error("failed insertion , for the BinaryHeap is full.");
		return ;	
	}
	bh->array[++bh->size] = e; // startup is 1 not 0.
	percolateUp(bh->size, bh);
}

 // percolating up the element when its value is greater than children (minimal heap)
 //Attention: all of bh->array starts from index 1
void percolateUp(int i, BinaryHeap bh)
{	
	ElementType temp = bh->array[i];
	
	for(; temp.value > bh->array[i/2].value; i/=2) // update.
	{
		bh->array[i] = bh->array[i/2];
	}
	bh->array[i] = temp;
}

// delete minimal from binary heap based on percolateDown().
ElementType deleteMin(BinaryHeap bh)
{	
	ElementType minimum;
	ElementType *data;				

	data = bh->array;	
	minimum = data[1];

	swap(&data[1], &data[bh->size]); // &variable means nickname of the variable
	bh->size-- ; // size-- occurs prior to percolateDown(). 
	percolateDown(1, bh) ;	

	return minimum;
} 

// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->array starts from index 1
 void percolateDown(int index, BinaryHeap bh)
 {  
    ElementType* array; 
    int size;
    ElementType temp;
    int child;

    array = bh->array;
    size = bh->size;

    for(temp = array[index]; leftChild(index) <= size; index = child)
    {
        child = leftChild(index);
        if(child < size && array[child].value < array[child+1].value)
		{
            child++;
		}
        if(temp.value < array[child].value)
		{
            array[index] = array[child];
		}
		else
		{
            break;
		}
    }
    array[index] = temp;
 }

// print binary heap.
void printBinaryHeap(BinaryHeap bh)
{
	int i;
	ElementType *temp;
	
	if(!bh)
	{
		Error("printing execution failure, for binary heap is NULL.");	
	}

	temp = bh->array;
	for(i = 1; i <= bh->size; i++)
	{
		printf("\n\t index[%d] = ", i);				
		printf("vertex[%c], num[%d]", bh->array[i].index+64, bh->array[i].value);
	}
	printf("\n");
}  
