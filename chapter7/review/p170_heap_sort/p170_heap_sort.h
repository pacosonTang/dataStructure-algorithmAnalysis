#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define Error(str) printf("\nerror: %s", str)

typedef int ElementType;
struct BinaryHeap;
typedef struct BinaryHeap* BinaryHeap;

struct BinaryHeap
{
	int capacity;
	int size;
	ElementType* array;
};

BinaryHeap buildHeap(int capacity);
void insert(BinaryHeap heap, ElementType data);
void percolateUp(BinaryHeap heap, ElementType data);
void deleteMin(BinaryHeap heap);
void percolateDown(BinaryHeap heap, int index);
void printBinaryHeap(ElementType *array, int size);
int leftChild(int index);
void swap(ElementType* a, ElementType* b);

// build binary heap with capacity.
BinaryHeap buildHeap(int capacity)
{
	BinaryHeap heap = (BinaryHeap)malloc(sizeof(struct BinaryHeap));

	if(!heap)
	{
		Error("failed buildHeap() for out of space.");
		return NULL;
	}
	heap->capacity = capacity;
	heap->size = 0; // startup of the heap is 1. so ++size when insert.
	
	// allocate memory for heap->array.
	heap->array = (ElementType*)malloc(sizeof(ElementType) * capacity);
	if(!heap->array)
	{
		Error("failed buildHeap() for out of space.");
		return NULL;
	}
	heap->array[0] = INT_MIN; // heap->array starts from 1 not 0, so let heap->array[0] = INT_MIN.
	return heap;
}

// 插入操作 based on 上滤操作.
void insert(BinaryHeap heap, ElementType data)
{
	if(heap->size == heap->capacity-1)
	{
		Error("failed insert() for heap is full.");
	}	
	percolateUp(heap, data);
}

// 上滤操作(key operation)
void percolateUp(BinaryHeap heap, ElementType data)
{
	int i;
		
	// 必须将size++.
	for(i=++heap->size; data < heap->array[i/2]; i/=2)
	{
		heap->array[i] = heap->array[i/2];
	}
	heap->array[i] = data;
}

// delete minimal from heap based on percolateDown().
void deleteMin(BinaryHeap heap)
{	
	if(heap->size==0)
	{
		Error("failed deleteMin() for the heap is empty");
		return ;
	}	
	swap(&heap->array[1], &heap->array[heap->size--]); // 将二叉堆的根和二叉堆的最后一个元素交换，size--。
	percolateDown(heap, 1); // 执行下滤操作.
}

// 下滤操作(key operation)
void percolateDown(BinaryHeap heap, int i)
{
	int child;
	int temp;	

	for(temp=heap->array[i]; (child=leftChild(i))<=heap->size; i=child)
	{				
		if(child<heap->size && heap->array[child] > heap->array[child+1])
		{
			child++;
		}
		if(temp > heap->array[child]) // 比较是和 temp=heap->array[index] 进行比较.
		{			
			heap->array[i] = heap->array[child];
		}
		else
		{					
			break;
		}
	}
	heap->array[i] = temp;	
}

int leftChild(int index)
{
	return 2*index;
}

// swap a and b.
void swap(ElementType* a, ElementType* b)
{
	ElementType t;

	t = *a;
	*a = *b;
	*b = t;
}

void printBinaryHeap(ElementType *array, int size)
{
	int i;

	for(i=1; i<=size; i++)
	{
		printf("\n\t heap->array[%d] = ", i);		
		printf("%d", array[i]);		
	}
	printf("\n");
} 



