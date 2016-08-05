#include "adjList.h"

void main()
{
	int capacity=7;	 // 顶点个数
	AdjList adjList;
	int row=7, col=3, i, j;
	int indegreeArray[7]; // 每个顶点的入度数组.
	Queue queue = initQueue(10);

	int adjArray[7][3] = 
	{
		{2, 4, 3},
		{4, 5, 0},
		{6, 0, 0},
		{6, 7, 3},
		{4, 7, 0},
		{0, 0, 0},
		{6, 0, 0}
	};
	
	// init adjacency list.
	adjList = init(7);	
	if(adjList==NULL)
	{
		return;
	}			
	
	printf("\n\n\t ====== review for topological sorting with adjacency list ======\n");			
	for(i=0; i<row; i++)
	{
		indegreeArray[i]=0;
	}
	for(i=0;i<row;i++)
	{		
		for(j=0;j<col;j++)
		{
			if(adjArray[i][j])
			{
				insertAdjList(adjList, i, adjArray[i][j]); // 插入节点到邻接表.
				indegreeArray[adjArray[i][j]-1]++; // 计算每个节点的入度.
			}
		}
	}
	printAdjList(adjList);
	printf("\n\t indegreeArray[] = ");
	printArray(indegreeArray, capacity);

	// 下面进行拓扑排序（用到了队列, 邻接表）.
	topSort(adjList, queue, indegreeArray);
}