#include "dfs.h"

extern char flag[];

void dfs(Vertex vertex, int depth)
{
	int i;
	AdjTable temp;
	Vertex adjVertex;	
	
	//printf("\n\t visited[%c] = 1 ", flag[vertex]);
	visited[vertex] = 1; // update visited status of vertex
	vertexIndex[vertex] = counter++; // number the vertex with counter
	temp = adj[vertex];	

	while(temp->next)
	{
		adjVertex = temp->next->vertex;		
		if(visited[adjVertex]) // judge whether the adjVertes was visited before		
		{
			if(vertexIndex[vertex] > vertexIndex[adjVertex] && parent[vertex] != adjVertex) 	
			{
				parent[adjVertex] = vertex; // building back side, attention of condition of building back side above
				
				// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("           ");
				printf("vertex[%c]->vertex[%c] (backside) \n", flag[vertex], flag[adjVertex]);
			}
		}
		
		else
		{
			parent[adjVertex] = vertex;
			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("           ");
			printf("vertex[%c]->vertex[%c] (building edge)\n", flag[vertex], flag[adjVertex]);			
			dfs(adjVertex, depth+1);
		}
		
		temp = temp->next;
	} 
} 
 
