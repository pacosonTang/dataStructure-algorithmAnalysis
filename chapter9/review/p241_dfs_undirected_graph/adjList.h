#include "top.h"

AdjList init(int capacity);
void insertAdjList(AdjList adjList, int start, int index, int weight);
void printAdjList(AdjList adjList);
Vertex create(int index, int weight);

// create vertex with identifier index.
Vertex create(int index, int weight)
{
	Vertex v = (Vertex)malloc(sizeof(struct Vertex));

	if(v==NULL)
	{
		Error("failed create() for out of space.");
		return NULL;
	}
	v->index=index;
	v->next=NULL;
	v->weight = weight;
	return v;
}

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

// 插入 顶点标识符index 到邻接表下标为 start 的位置, weight[start->index] = weight. 
void insertAdjList(AdjList adjList, int start, int index, int weight)
{
	Vertex temp = adjList->array[start];	
		
	while(temp->next)
	{
		temp = temp->next;
	}	
	temp->next = create(index, weight);
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
		printf("\t adjList[%c]-> ", i+1+64);
		temp = array[i];
		while(temp->next)
		{
			printf("%c ", temp->next->index+64);
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