#include <stdio.h>
#include <malloc.h>
#include <limits.h>

// 堆节点类型为 int.
#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   
#define ElementNum 7
#define SUM 10

struct BinaryHeap;
typedef struct BinaryHeap *BinaryHeap;
struct BinaryHeap 
{
	int capacity;
	int size;	
	ElementType *array;		
};

// 货物(箱子)结构体.
struct Good;
typedef struct Good* Good;
typedef struct Good* Box;
struct Good
{
	int value;  // 这里的value 对于货物 指代 货物重量.
				// 这里的value 对于箱子 指代 箱子的剩余容量.
	Good next;
};

// 定义一个仓库结构体， 包含多个箱子.
struct Warehouse;  // 仓库可以看多箱子数组.
typedef struct Warehouse* Warehouse;
struct Warehouse
{
	int capacity;
	int size;
	Box* array; // 多个箱子.
};

