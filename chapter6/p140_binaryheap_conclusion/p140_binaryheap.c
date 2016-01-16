#include "binaryheap.h"

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

	swap(&data[1], &data[bh->size]); // &variable means nickname of the variable
	bh->size-- ; // size-- occurs prior to percolateDownFromOne 
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
	{
		bh->elements[i] = bh->elements[i/2];
	}

	bh->elements[i] = value;
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

	return bh;
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
		}else
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

int parentIndex(int index)
{
	return index / 2;
}

// percolating up the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateUp(int index, BinaryHeap bh)
 {  
    ElementType *data;
    ElementType temp;
    int size;   
    int parent;

    data = bh->elements;
    size = bh->size;

    for(temp = data[index]; parentIndex(index) > 0; index = parent)
    {
        parent = parentIndex(index);
        if(parent == 0 || temp > data[parent])  
		{
            break;
		}
        else        
		{
            data[index] = data[parent];                                         
		}
    }
    data[index] = temp;
 }

int main()
{
	int i;
	BinaryHeap bh;
	int capacity;
	int size;
	ElementType data[] =  {85, 80, 40, 30, 10, 70, 110};

	capacity = 15;
	size = 7;
	bh = initBinaryHeap(capacity);

	printf("\n\t=== test for inserting the binary heap with {85, 80, 40, 30, 10, 70, 110} in turn ===\n");
	for(i = 0; i < size; i++)
	{
		insert(data[i], bh);
	}	
	printBinaryHeap(bh);

	printf("\n\t=== test for inserting the binary heap with {100, 20, 90, 5} in turn ===\n");
	insert(100, bh);
	insert(20, bh);
	insert(90, bh);
	insert(5, bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for a deleting towards the minimum in binary heap ===\n");
    deleteMin(bh);  
    printBinaryHeap(bh);    

	// other operations in bianry heap  
    printf("\n\t====== test for other operations in bianry heap as follows ======\n");
    printf("\n\t=== test for increaseKey(2, 85, bh) [increaseKey(index, increment, binary heap)] ===\n");
    increaseKey(2, 85, bh);
    printBinaryHeap(bh);
	
	printf("\n\t=== test for decreaseKey(9, 85, bh) [decreaseKey(index, decrement, binary heap)] ===\n");
    decreaseKey(9, 85, bh);
    printBinaryHeap(bh);
	
	return 0;
}