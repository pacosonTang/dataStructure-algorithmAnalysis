#include "adjList.h"

#define VertexNum 7

// 以下数组的 0 号下标 通通不用。
int visited[VertexNum+1]; // 顶点被访问状态 visited[i]==1|0(已访问|未访问)
int num[VertexNum+1]; // 顶点被访问的序号.
int parent[VertexNum+1]; // parent[i]=j 表明 顶点i 紧跟着顶点j之后 被访问.
int counter=0; // 已被访问的顶点数量.

// dfs 深度优先搜索算法.
// 邻接表adjList(图的标准表示方法)，vertexIndex 顶点索引，depth 用于打印空格，visted数组 用于存储 顶点访问状态.
void dfs_undirected_graph(AdjList adjList, int vertex, int depth)
{
	int i;
	Vertex temp = adjList->array[vertex-1];
	int adjVertex;
		
	visited[vertex] = 1; // 更新vertex 顶点为 已访问状态.
	num[vertex] = ++counter; // 顶点vertex 被访问的序号.	

	while(temp->next)
	{
		adjVertex = temp->next->index;		
		if(!visited[adjVertex]) // 邻接顶点没有被访问过, 则利用dfs 进行访问.
		{
			parent[adjVertex] = vertex;			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("           ");
			printf("v[%c]->v[%c] (build edge)\n", vertex+64, adjVertex+64);
			dfs_undirected_graph(adjList, adjVertex, depth+1);
		}				
		temp = temp->next;
	} 
} 