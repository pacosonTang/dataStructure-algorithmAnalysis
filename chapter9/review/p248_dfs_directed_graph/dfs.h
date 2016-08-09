#include "adjList.h"

#define VertexNum 10

int min(int a, int b);

// 0 号下标通通不用.
int visited[VertexNum+1]; // 顶点被访问状态 visited[i]==1|0(已访问|未访问)
int num[VertexNum+1]; // 顶点被访问的序号.
int parent[VertexNum+1]; // parent[i]=j 表明 顶点i 紧跟着顶点j之后 被访问.
int low[VertexNum+1]; // low[i]=j 表明 顶点i 可以访问(包括通过背向边)的最先被访问的顶点是顶点j.
int counter=0; // 已被访问的顶点数量.

// dfs 深度优先搜索算法. 遍历有向图.
// 邻接表adjList(图的标准表示方法)，vertexIndex 顶点索引，depth 用于打印空格
void dfs_find_directed_graph(AdjList adjList, int vertex, int depth)
{
	int i;
	Vertex temp = adjList->array[vertex-1];
	int adjVertex;
		
	visited[vertex] = 1; // 更新vertex 顶点为 已访问状态. vertex 从1开始取，所以减1.
	low[vertex] = num[vertex] = ++counter; // 顶点vertex 被访问的序号.	
	while(temp->next)
	{
		adjVertex = temp->next->index;		
		if(!visited[adjVertex]) // 邻接顶点没有被访问过, 则利用dfs 进行访问.
		{
			parent[adjVertex] = vertex;			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("           ");
			printf("v[%c]->v[%c] (build edge) \n", vertex+64, adjVertex+64);
			dfs_find_directed_graph(adjList, adjVertex, depth+1);						
			low[vertex] = min(low[vertex], low[adjVertex]); // 基于后序遍历更新low[].
		}	
		else // if(visited[adjVertex-1]) 邻接顶点被访问过.
		{			
			if(parent[vertex] != adjVertex) // true，则(vertex, adjVertex)就是背向边
			{
				low[vertex] = min(low[vertex], num[adjVertex]); // 更新 当前节点i的low[i]								
			} 			 			 
		}				
		temp = temp->next;
	} 	
} 

int min(int a, int b)
{
	return a>b? b:a;
}