#include <stdio.h>
#include <malloc.h>

#define Error(str) printf("\n error: %s", str)

// 顶点的结构体.
struct Vertex;
typedef struct Vertex* Vertex;
struct Vertex
{
	// ElementType value; // 要知道顶点是一个标识符，并不是真正的value(而是对value的抽象).
	int index;
	Vertex next;
};

// 邻接表的结构体
struct AdjList;
typedef struct AdjList* AdjList;
struct AdjList
{
	int capacity;
	Vertex* array;
};

AdjList init(int capacity);
void insertAdjList(AdjList adjList, int start, int index);
void printAdjList(AdjList adjList);

// initilizing the adjacency list with capacity
AdjList init(int capacity)
{
	int i;
	AdjList adjList = (AdjList)malloc(sizeof(struct AdjList));
	
	if(adjList==NULL)
	{
		Error("failed init() for out of space.");
		return NULL;
	}
	adjList->capacity = capacity;
	
	adjList->array = (Vertex*)malloc(capacity * sizeof(Vertex));	
	if(adjList->array==NULL)
	{
		Error("failed init() for out of space.");
		return NULL;
	}

	for(i=0; i<capacity; i++)
	{
		adjList->array[i] = (Vertex)malloc(sizeof(struct Vertex));
		if(adjList->array[i]==NULL)
		{
			Error("failed init() for out of space.");
			return NULL;
		}
		adjList->array[i]->next = NULL;
	}
	return adjList;
} 

// create vertex with index.
Vertex create(int index)
{
	Vertex v = (Vertex)malloc(sizeof(struct Vertex));

	if(v==NULL)
	{
		Error("failed create() for out of space.");
		return NULL;
	}
	v->index=index;
	v->next=NULL;
	return v;
}

// 插入 顶点标识符index 到邻接表下标为 start 的位置. 
void insertAdjList(AdjList adjList, int start, int index)
{
	Vertex temp = adjList->array[start];	
		
	while(temp->next)
	{
		temp = temp->next;
	}	
	temp->next = create(index);;	
	if(temp->next ==NULL)
	{
		return ;
	}
}

// 打印邻接表.
void printAdjList(AdjList adjList)
{
	int i;
	Vertex* array = adjList->array;
	Vertex temp;

	for(i = 0; i < adjList->capacity; i++)
	{
		printf("\t adjList[%d]-> ", i+1);
		temp = array[i];
		while(temp->next)
		{
			printf("%d ", temp->next->index);
			temp = temp->next;
		}	
		printf("\n");
	}	
}

void printArray(int* array, int size)
{
	int i;
		
	for(i=0; i<size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}