#include "adjList.h"

#define VertexNum 10

int min(int a, int b);

// 0 号下标通通不用.
int visited[VertexNum+1]; // 顶点被访问状态 visited[i]==1|0(已访问|未访问)
int num[VertexNum+1]; // 顶点被访问的序号.
int parent[VertexNum+1]; // parent[i]=j 表明 顶点i 紧跟着顶点j之后 被访问.
int counter=0; // 已被访问的顶点数量.

// dfs 深度优先搜索算法.
// 邻接表adjList(图的标准表示方法) , vertex 顶点索引，depth 用于打印空格
void dfs_find_strong_component(AdjList adjList, int vertex, int depth)
{
	int i;
	Vertex temp = adjList->array[vertex-1];
	int adjVertex;
		
	visited[vertex] = 1; // 更新vertex 顶点为 已访问状态. vertex 从1开始取，所以减1.	
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
			dfs_find_strong_component(adjList, adjVertex, depth+1);									
		}	
		else // if(visited[adjVertex-1]) 邻接顶点被访问过.
		{		
			if(parent[vertex] != adjVertex) // true，则(vertex, adjVertex)就是背向边
			{								
				// just for printing effect, 不作为算法的一部分.
				for(i = 0; i < depth; i++)  
					printf("           ");	
				printf("v[%c]->v[%c] (backside)\n", vertex+64, adjVertex+64);
				// 不作为算法的一部分over.
			} 			 			 
		}				
		temp = temp->next;
	} 	
	num[vertex] = ++counter; // 顶点vertex 被访问的序号. // attention, p249: 明确说明 使用dfs 后序遍历设置 顶点编号.
} 

int min(int a, int b)
{
	return a>b? b:a;
}