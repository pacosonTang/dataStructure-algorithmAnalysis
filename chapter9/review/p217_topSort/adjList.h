#include "queue.h"

struct Vertext;
typedef struct Vertex* Vertex;

struct Vertex
{
	// ElementType value; // 要知道顶点是一个标识符，并不是真正的value(而是对value的抽象).
	int index;
	Vertex next;
};

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

// 拓扑排序
void topSort(AdjList adjList, Queue queue, int* indegreeArray)
{
	int i;
	Vertex* array = adjList->array;
	Vertex temp;
	int index;
	int adjVertex;

	// step1: 把入度为0的顶点放入队列.
	for(i=0; i<adjList->capacity; i++) // 切记: 这里入队的value(或i) 从 0 开始取.
	{
		if(indegreeArray[i]==0) 
		{
			enQueue(queue, i);
		}
	}

	//step2: 当队列不为空时，一个顶点v出队，并将与v邻接的所有顶点的入度减1.
	printf("\n\t top sorting result: ");
	while(!isEmpty(queue))
	{
		index = deQueue(queue); // while 循环已经保证了 队列不可能为空.
		printf("v[%d] ", index+1); // 注意: 这里的index 要加1，因为元素入队是从 0 开始取的，见上面的入队操作.
		temp = array[index];
		while(temp->next)
		{
			adjVertex = temp->next->index; // 因为 temp->next->index 从1 开始取的,
			indegreeArray[adjVertex-1]--; // adjVertex 要减1, 而indegreeArray数组从0开始取.
			if(indegreeArray[adjVertex-1]==0) // step3: 把与顶点v(标识符=index)相邻的，且入度为0的顶点放入队列.
			{
				enQueue(queue, adjVertex-1); //入队的value(或index) 从 0 开始取.				
			}
			temp = temp->next;
		}
	}
	//  循环结束后: 拓扑排序就是顶点出队的顺序.
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