#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define Error(str) printf("\n error: %s", str)
// 堆节点类型是 结构体类型 而不是单纯的 int类型.
#define ElementType struct HeapNode 

// 顶点的结构体.
struct Vertex;
typedef struct Vertex* Vertex;
struct Vertex
{
	// ElementType value; // 要知道顶点是一个标识符，并不是真正的value(而是对value的抽象).
	int index;
	Vertex next;
	int weight; // 有权路径带有权值.
};

// 邻接表的结构体.
struct AdjList;
typedef struct AdjList* AdjList;
struct AdjList
{
	int capacity;
	Vertex* array;
};

// 堆节点类型是结构体.
struct HeapNode; 
typedef struct HeapNode* HeapNode;
struct HeapNode
{
	int index; // 节点编号 从 1 开始取.
	int value; // value == num[i] 节点被访问的序号.
};

// 二叉堆的结构体.
struct BinaryHeap;
typedef struct BinaryHeap *BinaryHeap;
struct BinaryHeap 
{
	int capacity;
	int size;	
	HeapNode array; // 二叉堆实现为结构体数组.
};