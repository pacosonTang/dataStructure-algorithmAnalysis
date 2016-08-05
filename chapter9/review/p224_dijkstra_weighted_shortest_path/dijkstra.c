#include "dijkstra.h"

extern BinaryHeap buildHeap(int capacity);

void main()
{
	int capacity=7;	 // 顶点个数
	AdjList adjList; // 邻接表
	int row=7, col=4, i, j;	 
	BinaryHeap heap; // 初始化二叉堆.
	int start = 3; // 起始顶点为3.	
	WeightedTable table;

	int adjArray[7][4] = 
	{
		{2, 4, 0, 0},
		{4, 5, 0, 0},
		{1, 6, 0, 0},
		{3, 5, 6, 7},
		{7, 0, 0, 0},
		{0, 0, 0, 0},
		{6, 0, 0, 0}
	};
	int weight[7][4] = 
	{
		{2, 1, 0, 0},
		{3, 10, 0, 0},
		{4, 5, 0, 0},
		{2, 2, 8, 4},
		{6, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 0, 0, 0}
	};
	
	// init adjacency list.
	adjList = init(7);	
	if(adjList==NULL)
	{
		return;
	}			
	printf("\n\n\t === revirw for dijkstra alg to compute weighted shortest path ===");
	printf("\n\t === build adjacency list ===\n");	 
	for(i=0;i<row;i++)
	{		
		for(j=0;j<col;j++)
		{
			if(adjArray[i][j])
			{
				insertAdjList(adjList, i, adjArray[i][j], weight[i][j]); // 插入节点到邻接表.
			}
		}
	}
	printAdjList(adjList);

	// 利用 地杰斯特拉求 有权最短路径.
	table = initWeightedTable(capacity);
	heap = buildHeap(10); // 初始化二叉堆.
	dijkstra(adjList, table, 1, heap); // startVertex=1.
	printWeightedtable(table, 1);
}