#include "dfs.h"

extern char flag[];

void dfs(Vertex vertex, int depth)
{
	int i;
	int visitFlag;
	AdjTable temp;
	Vertex adjVertex;	
	
	//printf("\n\t visited[%c] = 1 ", flag[vertex]);
	visited[vertex] = 1; // update visited status of vertex
	vertexIndex[vertex] = counter++; // number the vertex with counter
	temp = adj[vertex];	
	visitFlag = 0;	

	while(temp->next)
	{			 
		adjVertex = temp->next->vertex;		
		if(visited[adjVertex]) // judge whether the adjVertes was visited before		
		{
			if(vertexIndex[vertex] > vertexIndex[adjVertex] && parent[vertex] != adjVertex) 	
			{
			//	parent[adjVertex] = vertex; // building back side, attention of condition of building back side above
				
				// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("      ");
				printf("  v[%c]->v[%c] (backside) \n", flag[vertex], flag[adjVertex]);
			}			
		}
		
		//if(!visited[adjVertex])
		else
		{
			if(vertex == start)
				visitFlag = 1;
			parent[adjVertex] = vertex;
			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("      ");			
			printf("  v[%c]->v[%c] (building edge) \n", flag[vertex], flag[adjVertex]);
			dfs(adjVertex, depth+1);
		}

		if(vertex == start && visitFlag) //conducingt dfs for only one adjoining vertex in the given graph
			break;	
		temp = temp->next;	
	} 
} 

// print the set dfs generates
void dfsPathSet(Vertex vertex, int depth)
{
	int i;
	int visitFlag;
	AdjTable temp;
	Vertex adjVertex;	
	
	//printf("\n\t visited[%c] = 1 ", flag[vertex]);
	visited[vertex] = 1; // update visited status of vertex
	vertexIndex[vertex] = counter++; // number the vertex with counter
	temp = adj[vertex];	
	visitFlag = 0;	
	
	if(vertex == start)
		printf("\n\t v[%c]", flag[start]);
	while(temp->next)
	{			 
		adjVertex = temp->next->vertex;		
		if(visited[adjVertex]) // judge whether the adjVertes was visited before		
		{
			if(vertexIndex[vertex] > vertexIndex[adjVertex] && parent[vertex] != adjVertex) 	
			{
				parent[adjVertex] = vertex; // building back side, attention of condition of building back side above
				
				// just for printing effect
				//for(i = 0; i < depth; i++)  
				//	printf("      ");
				//printf("  v[%c]->v[%c] (backside) \n", flag[vertex], flag[adjVertex]);
			}			
		}
		
		//if(!visited[adjVertex])
		else
		{
			if(vertex == start)
				visitFlag = 1;
			parent[adjVertex] = vertex;
			
			// just for printing effect
			//for(i = 0; i < depth; i++)  
			//	printf("      ");			
			//printf("  v[%c]->v[%c] (building edge) \n", flag[vertex], flag[adjVertex]);
			printf("->v[%c]", flag[adjVertex]);
			dfsPathSet(adjVertex, depth+1);
		}

		if(vertex == start && visitFlag) //conducingt dfs for only one adjoining vertex in the given graph
			break;	
		temp = temp->next;	
	} 
} 
  
