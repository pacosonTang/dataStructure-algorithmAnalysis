#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct BinaryHeap;
typedef struct BinaryHeap *BinaryHeap;

struct BinaryHeap 
{
	int capacity;
	int size;	
	ElementType *elements;		
};

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
	bh->elements = temp;
	bh->elements[0] = INT_MIN; // let bh->elements[0] be the minimum integer.

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
	bh->elements[++bh->size] = value; // startup is 1 not 0.
	percolateUp(bh->size, bh);
}

 // percolating up the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
void percolateUp(int i, BinaryHeap bh)
{	
	ElementType temp = bh->elements[i];
	
	for(; temp < bh->elements[i/2]; i/=2)
	{
		bh->elements[i] = bh->elements[i/2];
	}
	bh->elements[i] = temp;
}

// delete minimal from binary heap based on percolateDown().
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

	swap(&data[1], &data[bh->size]); // &variable means nickname of the variable
	bh->size-- ; // size-- occurs prior to percolateDown(). 
	percolateDown(1, bh) ;	

	return minimum;
} 

// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateDown(int index, BinaryHeap bh)
 {  
    ElementType *data;
    int size;
    ElementType temp;
    int child;

    data = bh->elements;
    size = bh->size;

    for(temp = data[index]; leftChild(index) <= size; index = child)
    {
        child = leftChild(index);
        if(child < size && data[child] > data[child+1])
		{
            child++;
		}
        if(temp > data[child])
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
	ElementType *temp;
	
	if(!bh)
	{
		Error("printing execution failure, for binary heap is null, from func printBinaryHeap");	
	}

	temp = bh->elements;
	for(i = 1; i < bh->capacity; i++)
	{
		printf("\n\t index[%d] = ", i);
		if(i <= bh->size)
		{
			printf("%d", bh->elements[i]);
		}
		else
		{
			printf("NULL");
		}
	}
	printf("\n");
}  

// increase element's value
void increaseKey(int index, ElementType increment, BinaryHeap bh)
{   
    if(index > bh->size || index < 1)
    {
        Error(" failed increaseKey, since overstep the boundary! ");
        return ;
    }

    bh->elements[index] += increment; // update the element under given index
    percolateDown(index, bh);
}

//decreasing value of the element under index by increment
void decreaseKey(int index, ElementType decrement, BinaryHeap bh)
{   
    if(index > bh->size || index < 1)
    {
        Error(" failed decreaseKey, since overstep the boundary! ");
        return ;
    }

    bh->elements[index] -= decrement; // update the element under given index
    percolateUp(index, bh);
}