#include "adjList.h"

extern void insert(BinaryHeap heap, ElementType data);
extern ElementType deleteMin(BinaryHeap heap);
extern int isEmpty(BinaryHeap heap);

WeightedTable initWeightedTable(int size);
void dijkstra(AdjList adj, WeightedTable table, int startVertex, BinaryHeap heap);
void printWeightedtable(WeightedTable table, int startVertex);

//allocate the memory for initializing unweighted table
WeightedTable initWeightedTable(int size)
{	
	int i;
	WeightedTable table = (WeightedTable)malloc(sizeof(struct WeightedTable));
	
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
		table->array[i]->known = 0; // known 等于 0 or 1 表示 未知 or 已知.
		table->array[i]->dv= INT_MAX; // dv==distance 等于 INT_MAX 表示不可达.(有权路径表示weight)
		table->array[i]->pv = 0; // pv==path 等于 0 也表示不可达.
	}
	return table;
} 

//计算 startVertex顶点 到其他顶点的无权最短路径
// adj:邻接表（图的标准表示方法）, table: 计算有权最短路径的配置表，heap：用于选取最小权值的邻接顶点的小根堆.
void dijkstra(AdjList adj, WeightedTable table, int startVertex, BinaryHeap heap)
{		
	int capacity=adj->capacity;
	Vertex* arrayVertex = adj->array;
	Vertex temp;
	Entry* arrayEntry = table->array;
	int index; // 顶点标识符(从0开始取)
	int adjVertex;
	struct HeapNode node;
	int weight;

	//step1(初始状态): startVertex 顶点插入堆. startVertex 从1 开始取.
	node.vertex=startVertex-1; // 插入堆的 node.vertex 从 0 开始取，所以startVertex-1.
	node.weight=0;
	insert(heap, node); // 插入堆.
	arrayEntry[startVertex-1]->dv=0;
	arrayEntry[startVertex-1]->pv=0;
	// 初始状态over.

	// step2: 堆不为空，执行 deleteMin操作. 并将被删除顶点的邻接顶点插入堆.
	while(!isEmpty(heap))
	{		
		index = deleteMin(heap).vertex;  // index表示邻接表下标，从0开始取，参见插入堆的操作.
		arrayEntry[index]->known=1; // 从堆取出后，将其 known 设置为1.
		temp = arrayVertex[index];		
		while(temp->next) 
		{
			adjVertex = temp->next->index; // 邻接节点标识符adjVertex 从1开始取.
			weight = temp->next->weight; // 取出该邻接顶点的权值.

			if(arrayEntry[adjVertex-1]->known == 0) // 注意: 下标是adjVertex-1, 且known==0 表明 adjVertex顶点还处于未知状态,所以adjVertex插入堆.
			{
				if(arrayEntry[adjVertex-1]->dv > arrayEntry[index]->dv + weight ) // [key code] 当当前权值和 比 之前权值和 小的时候 才更新，否则不更新.
				{
					node.vertex=adjVertex-1; // 插入堆的 node.vertex 从 0 开始取.
					node.weight=weight;
					insert(heap, node); // 插入堆.
					arrayEntry[adjVertex-1]->dv = arrayEntry[index]->dv + weight; // [also key code]
					arrayEntry[adjVertex-1]->pv=index+1; // index 从0开始取，所以index加1.	
				}
			}			
			temp = temp->next;
		}
		 // printWeightedtable(table, 1); 取消这行注释可以 follow 迪杰斯特拉 alg 的运行过程.
	}	
} 

//print unweighted table
void printWeightedtable(WeightedTable table, int startVertex)
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

	// printf("\n\t unweighted shortest path table are as follows:\n");	
	printf("\n\t %6s%6s%9s%5s", str[0], str[1], str[2], str[3]);	
	for(i=0; i<size; i++)
	{		
		if(i != startVertex-1) 				
			printf("\n\t %-3d   %3d   %5d      v%-3d  ", i+1, array[i]->known, array[i]->dv, array[i]->pv);
		else
			printf("\n\t *%-3d  %3d   %5d      %-3d  ", i+1, array[i]->known, array[i]->dv, 0);
	}	 
	printf("\n");
}

 