#include "dfs.h"

extern ElementType createHeapNode(int index,int value);
extern BinaryHeap initBinaryHeap(int capacity);
extern void insert(ElementType value, BinaryHeap bh);
extern int isEmpty(BinaryHeap bh);
extern ElementType deleteMin(BinaryHeap);
extern void printBinaryHeap(BinaryHeap bh);

void main()
{
	int capacity=VertexNum;	 // 顶点个数
	AdjList adjList; // 邻接表
	AdjList adjListReverse; // 反向邻接表
	BinaryHeap heap; // 大根堆, 用于依次选取 序号最大的边. 堆节点类型是结构体, 因为要存储顶点编号和对应的被访问序号.
	int row=VertexNum, col=3, i, j;	 							
	int vertex;

	int adjArray[VertexNum][VertexNum] = 
	{
		{2, 4, 0}, // A
		{3, 6, 0}, // B
		{1, 4, 5}, // C
		{5, 0, 0}, // D
		{0, 0, 0}, // E
		{3, 0, 0}, // F
		{6, 8, 0}, // G
		{6, 10, 0}, // H
		{8, 0, 0}, // I
		{9, 0, 0}, // J
	};
	
	// init adjacency list.
	adjList = init(capacity);	
	if(adjList==NULL)
	{
		return;
	}			
	printf("\n\n\t === reviww for DFS applie into directed graph ===");
	printf("\n\t === build adjacency list ===\n");	 
	for(i=0;i<row;i++)
	{				
		for(j=0; j<col; j++)
		{
			if(adjArray[i][j])
			{
				insertAdjList(adjList, i, adjArray[i][j], adjArray[i][j]); // 插入节点到邻接表.(无向图权值为全1)
			}
		}
	}
	printAdjList(adjList);
	
	// 使用 dfs 查找强连通分支.
	// step1: 基于dfs 遍历 有向图G，对顶点的访问顺序编号.
	printf("\n=== dfs_find_directed_graph(adjList, 2, 1) ===\n");
	dfs_find_strong_component(adjList, 2, 1);	 // start=1.
	for(i=1; i<=VertexNum; i++)
	{
		if(!visited[i])
		{
			printf("\n");
			dfs_find_strong_component(adjList, i, 1);
		}
	}// step1 over.
	printf("\n\t === num array are as follows. ===");
	printArray(num, VertexNum+1);		

	//step2: 把G的所有边反向 -> Gr.
	adjListReverse = init(capacity);	
	if(adjListReverse==NULL)
	{
		return;
	}				
	printf("\n\t === build reverse adjacency list ===\n");
	for(i=0;i<row;i++)
	{			
		for(j=0; j<col; j++)
		{
			if(adjArray[i][j])
			{
				insertAdjList(adjListReverse, adjArray[i][j]-1, i+1, adjArray[i][j]); // 插入节点到邻接表.(无向图权值为全1)
			}
		}
	} // step2 over.
	printAdjList(adjListReverse);	 

	// step3: 从序号最大的顶点开始，依次对Gr 进行 dfs.（这里需要建立一个大根堆）	
	// step3.1: 利用num[] 建立大根堆
	heap = initBinaryHeap(VertexNum+1); // 因为0号下标不用.
	for(i=1; i<=VertexNum; i++)
	{
		insert(createHeapNode(i, num[i]), heap);
		// 初始化数组为0
		visited[i] = 0;
		num[i] = 0;				
		parent[i] = 0;	
	} // step3.1 over.
	printf("\n\t === binary heap is as follows.===");
	printBinaryHeap(heap);
	counter=0; // 初始化count=0；

	// step3.2 依次选取 最大序号的顶点进行dfs
	printf("\n=== dfs_find_strong_component(adjListReverse, deleteMin(heap).index, 1) ===\n");
	
	while(!isEmpty(heap) && counter!=VertexNum)
	{			
		vertex = deleteMin(heap).index; // 依次选取 最大访问序号的顶点.		
		if(!visited[vertex]) // 如果该顶点没有被访问的话.
		{
			dfs_find_strong_component(adjListReverse, vertex, 1);
		}		
	}	
}