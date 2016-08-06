#include "top.h"

// 堆节点类型是 结构体指针类型 而不是单纯的 int类型.
#define ElementType HeapNode 

void swap(ElementType x, ElementType y);
int leftChild(int index);
BinaryHeap initBinaryHeap(int capacity);
void insert(ElementType value, BinaryHeap bh);
ElementType deleteMin(BinaryHeap);
int isFull(BinaryHeap bh);
int isEmpty(BinaryHeap bh);
void percolateUp(int index, BinaryHeap bh);
void percolateDown(int index, BinaryHeap bh);
void printBinaryHeap(BinaryHeap bh);

ElementType createElementType(int value)
{
	HeapNode node = (HeapNode)malloc(sizeof(struct HeapNode));
	if(node == NULL)
	{
		Error("failed createElementType() for out of space.");        
        return NULL;
	}
	node->value = value;
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

void swap(ElementType x, ElementType y)
{
	struct HeapNode temp;

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
	ElementType* temp;

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
	// bh->array[0] = INT_MIN; 
	bh->array[0] = (ElementType)malloc(sizeof(struct HeapNode));
	if(bh->array[0] == NULL)
	{
		Error("out of space, from func initBinaryHeap");        
        return NULL;
	}
	bh->array[0]->value = INT_MIN; 
	return bh;
}

// Attention, the index of the heap starts from 1
// insert the value into binary heap based on percolateUp().
void insert(ElementType e, BinaryHeap bh)
{		
	if(e == NULL)
	{
		Error("failed insertion , for e is NULL.");
		return;
	}
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
	
	for(; temp->value < bh->array[i/2]->value; i/=2) // update.
	{
		bh->array[i] = bh->array[i/2];
	}
	bh->array[i] = temp;
}

// delete minimal from binary heap based on percolateDown().
ElementType deleteMin(BinaryHeap bh)
{	
	ElementType minimum;
	ElementType* array;				

	array = bh->array;	
	minimum = array[1];

	swap(array[1], array[bh->size]); // &variable means nickname of the variable
	bh->size-- ; // size-- 在下滤函数执行之前发生.
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
        if(child < size && array[child]->value > array[child+1]->value)
		{
            child++;
		}
        if(temp->value > array[child]->value)
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
	
	if(!bh)
	{
		Error("printing execution failure, for binary heap is NULL.");	
		return;
	}
	
	for(i=1; i <= bh->size; i++)
	{
		printf("\n\t index[%d] = ", i);				
		printf("%d", bh->array[i]->value);		
	}
	printf("\n");
}  

// increase element's value
void increaseKey(int index, int increment, BinaryHeap bh)
{   
    if(index > bh->size || index < 1)
    {
        Error(" failed increaseKey, since overstep the boundary! ");
        return ;
    }

    bh->array[index]->value += increment; // update the element under given index
    percolateDown(index, bh);
}

//decreasing value of the element under index by increment
void decreaseKey(int index, int decrement, BinaryHeap bh)
{   
    if(index > bh->size || index < 1)
    {
        Error(" failed decreaseKey, since overstep the boundary! ");
        return ;
    }

    bh->array[index]->value -= decrement; // update the element under given index
    percolateUp(index, bh);
}