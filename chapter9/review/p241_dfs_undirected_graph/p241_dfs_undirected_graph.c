#include "dfs.h"

void main()
{
	int capacity=VertexNum;	 // 顶点个数
	AdjList adjList; // 邻接表
	int row=VertexNum, i, j;	 							

	int adjArray[VertexNum][VertexNum] = 
	{
		{0, 1, 0, 1, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 0},
		{0, 0, 0, 1, 0, 1, 0},
		{0, 0, 0, 1, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0},
	};
	
	// init adjacency list.
	adjList = init(capacity);	
	if(adjList==NULL)
	{
		return;
	}			
	printf("\n\n\t === review for DFS applie into undirected graph ===");
	printf("\n\t === build adjacency list ===\n");	 
	for(i=0;i<row;i++)
	{		
		visited[i]=0;
		for(j=0; j<row; j++)
		{
			if(adjArray[i][j])
			{
				insertAdjList(adjList, i, j+1, adjArray[i][j]); // 插入节点到邻接表.(无向图权值为全1)
			}
		}
	}
	printAdjList(adjList);

	// traverse the undirected graph using dfs.
	printf("\n === dfs_undirected_graph(adjList, 1, 1) ===\n");
	dfs_undirected_graph(adjList, 1, 1);
}