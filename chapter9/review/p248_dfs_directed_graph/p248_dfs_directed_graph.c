#include "dfs.h"

extern int low[VertexNum+1];
int start=1;
extern int visited[VertexNum+1];

void main()
{
	int capacity=VertexNum;	 // 顶点个数
	AdjList adjList; // 邻接表
	int row=VertexNum, col=3, i, j;	 							

	int adjArray[VertexNum][VertexNum] = 
	{
		{2, 4, 0},
		{3, 6, 0},
		{1, 4, 5},
		{5, 0, 0},
		{0, 0, 0},	
		{3, 0, 0},	
		{6, 8, 0},
		{6, 10, 0},
		{8, 0, 0},
		{9, 0, 0},
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
		visited[i]=0;
		for(j=0; j<col; j++)
		{
			if(adjArray[i][j])
			{
				insertAdjList(adjList, i, adjArray[i][j], adjArray[i][j]); // 插入节点到邻接表.(无向图权值为全1)
			}
		}
	}
	printAdjList(adjList);
	
	// 使用 dfs 遍历有向图.
	printf("\n=== dfs_find_directed_graph(adjList, 2, 1) ===\n");
	dfs_find_directed_graph(adjList, 2, 1);	 // step1:

	for(i=1; i<=VertexNum; i++) // step2:
	{
		if(!visited[i])
		{
			printf("\n");
			dfs_find_directed_graph(adjList, i, 1);
		}
	}
}