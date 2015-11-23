#include "dfs.h"

extern char flag[];

void dfs(Vertex vertex)
{
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
			if(vertexIndex[vertex] < vertexIndex[adjVertex] && parent[vertex] != adjVertex)
				insertAdj(backsides, adjVertex, vertex); // building back side, attention of condition of building back side above					
		}
		//while(!visited[adjVertex])
		else
		{
			parent[adjVertex] = vertex;
			dfs(adjVertex);
		}
		
		temp = temp->next;
	} 
} 

// print DFS' traversal order for the given graph
void printTraversalOrder()
{
	int i;
	
	printf("\n\t === DFS' traversal sequence for the graph is as follows: === ");
	for(i=0; i<size; i++)	 
		printf("\n\t vertex[%c] = sequence[%d]", flag[i], vertexIndex[i]);	 
	
	printf("\n");
}

// print parent array for showing vertexes' parent
void printParentArray()
{
	int i;
	
	printf("\n\t === showing vertexes' parents: === ");
	for(i=0; i<size; i++)
		if(parent[i] == size)
			printf("\n\t vertex[%c]->parent = NULL", flag[i], flag[parent[i]]);	 
		else
		printf("\n\t vertex[%c]->parent = vertex[%c]", flag[i], flag[parent[i]]);	 
	
	printf("\n");
}

// print parent array for showing vertexes' parent
void printBacksides()
{
	int i;
	AdjTable temp;
	
	printf("\n\t === showing vertexes' backsides: === ");
	for(i=0; i<size; i++)	 
	{
		temp = backsides[i];
		if(temp->next)
			printf("\n\t vertex[%c]", flag[i]);
		while(temp->next)
		{
			printf(" -> vertex[%c]", flag[temp->next->vertex]);
			temp = temp->next;
		}		
	}
	
	printf("\n");
}
