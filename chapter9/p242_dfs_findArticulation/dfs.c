#include "dfs.h"

extern char flag[];

int minimum(int a, int b)
{
	return a > b ? b : a;
}

int isStartArticulation()
{
	int i;	
	AdjTable temp;
	Vertex adjVertex;	
	 
	temp = adj[start];	

	while(temp->next)
	{
		adjVertex = temp->next->vertex;	
		if(adjVertex == start)
		{
			temp = temp->next;
			continue;
		}

		dfs(adjVertex, 1);		
		for(i=0; i<size; i++)		
			if(visited[i] != 1) // refers that the start vertex is the articulation point
				return 1;		 

		temp = temp->next;
	}

	return 0;
}

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
			//	parent[adjVertex] = vertex; // building back side, attention of condition of building back side above				
			
				// just for printing effect
				//for(i = 0; i < depth; i++)  
				//	printf("           ");
				//printf("vertex[%c]->vertex[%c] (backside) \n", flag[vertex], flag[adjVertex]);
				// printing effect over
			}
		}
		
		else
		{
			parent[adjVertex] = vertex;			
			
			// just for printing effect
			//for(i = 0; i < depth; i++)  
			//	printf("           ");
			//printf("vertex[%c]->vertex[%c] (building edge)\n", flag[vertex], flag[adjVertex]);			
			// printing effect over

			dfs(adjVertex, depth+1);
		}
		
		temp = temp->next;
	} 
} 

void printVertexIndex(int *array, int size)
{
	int i;
	
	printf("\n\t=== vertexIndex array is as follows ===");
	for(i=0; i<size; i++)
		if(array[i] != -1)
			printf("\n\t vertexIndex[%c] = %d", flag[i], array[i]+1);
	printf("\n");
}

void printVertexLow(int *array, int size)
{
	int i;
	
	printf("\n\t=== vertexLow array is as follows ===");
	for(i=0; i<size; i++)
		if(array[i] != -1)
			printf("\n\t vertexLow[%c] = %d", flag[i], array[i]+1);
	printf("\n");
}

// find the articulation point from the given graph
void findArticulate(Vertex vertex, int depth)
{	
	int i;
	AdjTable temp;	
	Vertex adjVertex;						
		
	visited[vertex] = 1; // update visited status of vertex
	vertexIndex[vertex] = counter++; // evaluating vertex index with counter
	vertexLow[vertex] = vertexIndex[vertex]; // the 1st rule: evaluating vertex low with counter
	temp = adj[vertex];	

	while(temp->next)
	{
		adjVertex = temp->next->vertex;		
		if(visited[adjVertex]) // judge whether the adjVertes was visited before		
		{
			if(vertexIndex[vertex] > vertexIndex[adjVertex] && parent[vertex] != adjVertex) 	
			{
				parent[adjVertex] = vertex; // building back side, attention of condition of building back side above				
				//ex vertex= 3, adjVertex = 0

				// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("           ");
				printf("vertex[%c]->vertex[%c] (backside) \n", flag[vertex], flag[adjVertex]);
				
				// only if there's a backside, we apply the 2rd rule into the graph
				vertexLow[vertex] = minimum(vertexLow[vertex], vertexIndex[adjVertex]); // the 2rd rule: find lowest vertexIndex[w] among all edges(v, w)  
			}
		}
		
		// if(!visited[adjVertex])
		// there's the case no backside, and if condition sentences refers to case of backside
		else 
		{
			parent[adjVertex] = vertex;			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("           ");
			printf("vertex[%c]->vertex[%c] (building edge)\n", flag[vertex], flag[adjVertex]);			
			findArticulate(adjVertex, depth+1);
			
			if(vertex != start) // judge whether the vertex is the start (root) or not			
				if(vertexLow[adjVertex] >= vertexIndex[vertex])
					printf("\n\t vertex[%c] proves to be an articulation point !", flag[vertex]);
			 			 
			vertexLow[vertex] = minimum(vertexLow[vertex], vertexLow[adjVertex]); // the 3rd rule: find lowest verdexLow[w] among all edges(v, w)		
		}
		
		temp = temp->next;				
	} 
}  
