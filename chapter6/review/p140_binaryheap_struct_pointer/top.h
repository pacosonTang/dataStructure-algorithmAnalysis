#include <stdio.h>
#include <malloc.h>
#include <limits.h>

// #define ElementType int 堆节点是结构体类型
#define Error(str) printf("\n error: %s \n",str)   

struct HeapNode; 
typedef struct HeapNode* HeapNode;
struct HeapNode
{
	int value;
};

// 二叉堆的结构体.
struct BinaryHeap;
typedef struct BinaryHeap *BinaryHeap;
struct BinaryHeap 
{
	int capacity;
	int size;	
	HeapNode* array;  // 堆节点类型是结构体指针. 而优先队列是结构体指针数组.
};