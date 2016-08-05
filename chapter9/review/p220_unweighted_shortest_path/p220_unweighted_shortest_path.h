#include "adjList.h"
#include <limits.h>

// 记录表的表项
struct Entry;
typedef struct Entry* Entry;
struct Entry
{
	int known;
	int dv;
	int pv;
};

// 记录表的数组
struct UnweightedTable;
typedef struct UnweightedTable* UnweightedTable;
struct UnweightedTable
{	
	int size;	
	Entry* array;
};

UnweightedTable initUnweightedTable(int size);
void printUnweightedtable(UnweightedTable table, int startVertex);

//allocate the memory for initializing unweighted table
UnweightedTable initUnweightedTable(int size)
{	
	int i;
	UnweightedTable table = (UnweightedTable)malloc(sizeof(struct UnweightedTable));
	
	if(table==NULL)
	{
		Error("failed initUnweightedTable() for out of space.");
		return NULL;
	}
	table->size = size;
	
	table->array = (Entry*)malloc(size * sizeof(Entry));	
	if(table->array==NULL)
	{
		Error("failed initUnweightedTable() for out of space.");
		return NULL;
	}

	for(i=0; i<size; i++)
	{
		table->array[i] = (Entry)malloc(sizeof(struct Entry));
		if(table->array[i]==NULL)
		{
			Error("failed initUnweightedTable() for out of space.");
			return NULL;
		}
		table->array[i]->known = 0; // known=0 or 1表示 未知 或 已知.
		table->array[i]->dv= INT_MAX; // dv==distance 等于 INT_MAX 表示不可达. 而 dv=0 表示它自己到自己的path==0.
		table->array[i]->pv = 0; // pv==path 等于 0 表示不可达，因为pv从1开始取。
	}
	return table;
} 

//计算 startVertex顶点 到其他顶点的无权最短路径
void unweighted_shortest_path(AdjList adj, UnweightedTable table, int startVertex, Queue queue)
{		
	int capacity=adj->capacity;
	Vertex* arrayVertex = adj->array;
	Vertex temp;
	Entry* arrayEntry = table->array;
	int index; // 顶点标识符(从0开始取)
	int adjVertex;

	//step1(初始状态): startVertex 顶点进队.
	enQueue(queue, startVertex-1); // 切记: 这里入队的value(或i) 从 0 开始取.	
	arrayEntry[startVertex-1]->dv=0;
	arrayEntry[startVertex-1]->pv=0;
	// 初始状态over.

	// step2: 出队. 并将其出队顶点的邻接顶点进队.
	while(!isEmpty(queue))
	{
		index = deQueue(queue);  // index从0开始取，因为出队value从0开始取，不需要减1.
		arrayEntry[index]->known=1; // 出队后，将其 known 设置为1.
		temp = arrayVertex[index];
		while(temp->next) 
		{
			adjVertex = temp->next->index; // 邻接节点标识符adjVertex 从1开始取.
			if(arrayEntry[adjVertex-1]->dv == INT_MAX) // 注意: 下标是adjVertex-1, 且 dv==INT_MAX 表明 index 到 adjVertex 还处于不可达状态，所以adjVertex入队.
			{
				enQueue(queue, adjVertex-1); // 入队的value 从 0 开始取，所以减1.
				arrayEntry[adjVertex-1]->dv = arrayEntry[index]->dv + 1; 
				arrayEntry[adjVertex-1]->pv=index+1; // index 从0开始取，所以index加1.
			}			
			temp = temp->next;
		}		
	}	
} 

//print unweighted table
void printUnweightedtable(UnweightedTable table, int startVertex)
{
	int i;
	Entry* array = table->array;
	int size=table->size;
	char *str[4] = 
	{
		"vertex",
		"known",
		"distance",
		"path"
	};

	printf("\n\t unweighted shortest path table are as follows:\n");	
	printf("\n\t %6s%6s%9s%5s", str[0], str[1], str[2], str[3]);	
	for(i=0; i<size; i++)
	{		
		if(i != startVertex-1) 				
			printf("\n\t %-3d   %3d   %5d      %-3d  ", i+1, array[i]->known, array[i]->dv, array[i]->pv);
		else
			printf("\n\t *%-3d  %3d   %5d      %-3d  ", i+1, array[i]->known, array[i]->dv, 0);
	}	 
	printf("\n");
}

 