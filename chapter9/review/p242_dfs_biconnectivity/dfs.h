#include "adjList.h"

#define VertexNum 7

int min(int a, int b);

// 下列数组 0 号下标通通不用.
int visited[VertexNum+1]; // 顶点被访问状态 visited[i]==1|0(已访问|未访问)
int num[VertexNum+1]; // 顶点被访问的序号.
int parent[VertexNum+1]; // parent[i]=j 表明 顶点i 紧跟着顶点j之后 被访问.
int low[VertexNum+1]; // low[i]=j 表明 顶点i 可以访问(包括通过背向边)的最先被访问的顶点是顶点j.
int counter=0; // 已被访问的顶点数量.

// dfs 深度优先搜索算法.用于寻找背向边和割点.
// 邻接表adjList(图的标准表示方法)，vertexIndex 顶点索引，depth 用于打印空格
void dfs_find_articulation(AdjList adjList, int vertex, int depth)
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
			printf("v[%c]->v[%c] (build edge) (%c, %d/%d)\n", vertex+64, adjVertex+64, vertex+64, num[vertex], low[vertex]);
			dfs_find_articulation(adjList, adjVertex, depth+1);
			
			if(low[adjVertex] >= num[vertex]) // 判断 vertex是否是割点.
			{
					// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("           ");
				printf("%c is an articulation point for (low[%c]=%d) >= (num[%c]=%d)\n", vertex+64, adjVertex+64, low[adjVertex], vertex+64, num[vertex]);
			}
			low[vertex] = min(low[vertex], low[adjVertex]); // 基于后序遍历更新low[].
		}	
		else // 邻接顶点被访问过.
		{						
			if(parent[vertex] != adjVertex) // true，则(vertex, adjVertex)就是背向边
			{
				low[vertex] = min(low[vertex], num[adjVertex]); // 更新 当前节点i的low[i]				
				// just for printing effect, 不作为算法的一部分.
				for(i = 0; i < depth; i++)  
					printf("           ");	
				// 不作为算法的一部分over.
				printf("v[%c]->v[%c] (backside) (%c, %d/%d)\n", vertex+64, adjVertex+64, vertex+64, num[vertex], low[vertex]);				
			} 			 			 
		}				
		temp = temp->next;
	} 
} 

int min(int a, int b)
{
	return a>b? b:a;
}