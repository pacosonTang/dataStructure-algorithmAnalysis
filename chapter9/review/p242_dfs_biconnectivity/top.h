#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define Error(str) printf("\n error: %s", str)
 
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
