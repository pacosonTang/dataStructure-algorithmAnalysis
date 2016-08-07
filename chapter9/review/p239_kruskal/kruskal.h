#include "adjList.h"

void kruskal(BinaryHeap heap, int* setArray, Edge* edgeSet, int size) ;
BinaryHeap buildHeapWithAdjList(AdjList adjList);
void printEdgeSet(Edge* array, int size);
extern int isEmpty(BinaryHeap bh);
ElementType deleteMin(BinaryHeap);
extern BinaryHeap initBinaryHeap(int capacity);
extern ElementType createHeapNode(int v1, int v2, int value);
extern void insert(ElementType value, BinaryHeap bh);

int stack[255];

// 创建大小为 size 的边集合数组，并赋值 a[i]=i. 0 号下标不用.
int* buildSet(int size) // set数组大小 等于 顶点个数+1，因为0号下标不用.
{
	int i;
	int* array = (int*)malloc(sizeof(int) * size);
	if(array == NULL)
	{
		Error("failed buildArray() for out of space");
		return NULL;
	}

	for(i=0; i<size; i++)
	{
		array[i] = i;
	}
	return array;
}

// 寻找 index标识的 顶点 所在的集合.
// find() 涉及到路径压缩，路径压缩 基于 栈来实现（先进后出）.
int find(int* setArray, int index)
{
	int temp = index;
	int i=0;			
			
	while(index != setArray[index])
	{
		stack[i++] = index; // index 从 1 开始取，stack 的元素 也从 1 开始取.
		index = setArray[index]; // setArray 下标从1 开始.
	}	
		
	// 下面进行路径压缩(基于栈的观点). 
	while(--i >= 0)
	{
		setArray[ stack[i] ] = index;
	}	

	return index;
} 

// 克鲁斯卡尔算法 用于寻找 最小生成树.
// 为什么这里没有把 邻接表作为参数传进来，因为即使将其作为参数，其还是要转化为 堆，
// 所以，为了算法的简洁性，在调用 kruskal() 方法前 就将 邻接表转化为 二叉堆优先队列了.
void kruskal(BinaryHeap heap, int* setArray, Edge* edgeSet, int edgeNum)  // 当顶点数=7时，edgeNum=6 因为 7个顶点最多6条边.
{
	int i=0;
	Edge edge;
	int set1, set2;

	while(!isEmpty(heap) && i<edgeNum)
	{
		edge = deleteMin(heap); // edge 不可能为空，因为heap 不为空（while循环）。
		set1 = find(setArray, edge->v1);
		set2 = find(setArray, edge->v2);

		// 克鲁斯卡尔算法就是要决定边 应该添加还是应该放弃
		if(set1 != set2) // 如果 v1 和 v2 不属于同一个集合，边就进行合并.
		{
			// setUnion begins.
			edgeSet[i++] = edge; // 添加边.			
			setArray[set2] = set1; //更新 edge->v2 的根的 集合标识. 而不能写成setArray[edge->v2] = set1;
			// setUnion over.
		}
	}
}	

// 用邻接表的数据建堆.
BinaryHeap buildHeapWithAdjList(AdjList adjList)
{	
	int i, capacity = adjList->capacity;
	Vertex vertex;
	Vertex* array = adjList->array;
	Edge edge;
	BinaryHeap heap = initBinaryHeap((capacity-1)*(capacity-1) + 1); // 因为 capacity个顶点最多产生(capacity-1)^2 条边.因为0号下标不用,所以加1.		
	if(heap==NULL)
	{
		Error("failed buildHeapWithAdjList() for out of space.");
		return NULL;
	}

	for(i=0; i<capacity; i++)
	{
		vertex = array[i];
		while(vertex->next)
		{
			if(i+1 < vertex->next->index)
			{
				edge = createHeapNode(i+1, vertex->next->index, vertex->next->weight);
				insert(edge, heap);
			}			
			vertex = vertex->next;
		}
	}
	return heap;
}

void printEdgeSet(Edge* array, int size)
{
	int i;
	
	for(i=0; i<size; i++)
	{
		printf("\n\tv[%d] -weight[%d]- v[%d]", array[i]->v1, array[i]->weight, array[i]->v2);
	}
	printf("\n");
}