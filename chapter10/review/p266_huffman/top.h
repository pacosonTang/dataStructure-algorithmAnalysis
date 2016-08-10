#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define Error(str) printf("\n error: %s", str)
#define ElementNum 7

// 堆节点类型是 结构体指针类型 而不是单纯的 int类型.
#define ElementType HeapNode 

// 二叉堆的堆节点类型为 结构体指针类型. 
struct HeapNode; 
typedef struct HeapNode* HeapNode;
struct HeapNode
{
	int value; // 字符出现的频率
	char flag; // 字符标识
	HeapNode left;
	HeapNode right;
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

struct HuffmanCode;
typedef struct HuffmanCode* HuffmanCode;
struct HuffmanCode                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
{
	char flag;
	char code[ElementNum-2+1]; // 因为还有 '\0'
	// 为什么 code的长度是ElementNum-2，因为 如元素个数是7，其最大高度为5. 
};