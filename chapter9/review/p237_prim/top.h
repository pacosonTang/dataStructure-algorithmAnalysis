#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define Error(str) printf("\n error: %s", str)
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

// 二叉堆的节点类型的结构体.
struct HeapNode;
typedef struct HeapNode* HeapNode;
struct HeapNode
{
	int vertex;
	int weight;
};

// 二叉堆的结构体.
struct BinaryHeap;
typedef struct BinaryHeap* BinaryHeap;
struct BinaryHeap
{
	int capacity;
	int size;
	HeapNode array;
};

// 邻接表的表项结构体.
struct Entry;
typedef struct Entry* Entry;
struct Entry
{
	int known;
	int dv;
	int pv;
};

// 有权路径记录表的结构体.
struct UnWeightedTable;
typedef struct UnWeightedTable* UnWeightedTable;

struct UnWeightedTable
{	
	int size;	
	Entry* array;
};