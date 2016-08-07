#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define Error(str) printf("\n error: %s", str)
#define ElementType HeapNode // 堆节点类型是　结构体指针类型．

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
struct Edge;
typedef struct Edge* Edge;
typedef struct Edge* HeapNode;
struct Edge
{
	int v1; // start
	int v2; // end
	int weight; // 顶点v1 和 v2 间的 权值.
};

// 二叉堆的结构体(由指针数组实现).
struct BinaryHeap;
typedef struct BinaryHeap* BinaryHeap;
struct BinaryHeap
{
	int capacity;
	int size;
	HeapNode* array; // 结构体指针数组.
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