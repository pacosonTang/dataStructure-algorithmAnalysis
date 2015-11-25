#include "dfs.h"

extern char flag[];

int minimum(int a, int b)
{
	return a > b ? b : a;
}

//judge whether the adjoining vertex of giben vertex  was visited or not , also return index unvisited vertex or -1;
int hasAdjVertex(Vertex vertex)
{
	AdjTable temp;	

	temp = adj[vertex];
	
	return temp->next != NULL;	
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
				//parent[adjVertex] = vertex; // building back side, attention of condition of building back side above				
			
				// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("      ");
				printf("v[%d]->v[%d] (backside) \n", vertex+1, adjVertex+1);
				 //printing effect over				
			}
		}
		
		else
		{
			//if(vertex == start)
			//	visitFlag = 1;
			parent[adjVertex] = vertex;			
			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("      ");
			printf("v[%d]->v[%d] (building edge)\n", vertex+1, adjVertex+1);			
			// printing effect over

			dfs(adjVertex, depth+1);
		}	
		//if(vertex == start && visitFlag) //conducingt dfs for only one adjoining vertex in the given graph
		//	break;
		temp = temp->next;
	} 	
}  

// find the euler path
/* version 1.0 */
void findEulerPath(Vertex vertex, int depth)
{
	int i;	
	AdjTable temp;
	Vertex adjVertex;	

	//printf("\n\t visited[%c] = 1 ", flag[vertex]);
	//visited[vertex] = 1; // update visited status of vertex
	vertexIndex[vertex] = counter++; // number the vertex with counter
	temp = adj[vertex];		
		
	while(temp->next)
	{
		adjVertex = temp->next->vertex;		
		if(visited[adjVertex]) // judge whether the adjVertes was visited before		
		{
			if(parent[vertex] != adjVertex) 	
			{
				//parent[adjVertex] = vertex; // building back side, attention of condition of building back side above				
			
				// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("      ");
				printf("v[%d]->v[%d] (backside) \n", vertex+1, adjVertex+1);				
				 //printing effect over
												
				deleteLastEuler(vertex);				
			}
		}		
		else
		{	
			visited[vertex] = 1; // update visited status of vertex
			parent[adjVertex] = vertex;			
			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("      ");
			printf("v[%d]->v[%d] (building edge)\n", vertex+1, adjVertex+1);			
			// printing effect over
			
			// building euler path
			if(!isVertexInPath(vertex))
				buildEuler(vertex);			
			buildEuler(adjVertex);
			// building over			
									
			findEulerPath(adjVertex, depth+1);
		}	 			 		

		if(adjVertex == start) //conducingt dfs for only one adjoining vertex in the given graph
		{
			visitFlag = 1;
			buildEuler(vertex);
			deleteAdj(adj, vertex, adjVertex);
		}
		if(visitFlag)
			return ;
		temp = temp->next;
	} 	
} 

// add vertex into the euler path 
void buildEuler(Vertex vertex)
{
	AdjTable temp;	

	temp = viceEulerPath;
	while(temp->next)	
		temp = temp->next;
	temp->next = makeEmptyAdj();
	temp->next->vertex = vertex;	 		
}

// judge whether the vertex in the euler path or not, also 1 or 0
int isVertexInPath(Vertex vertex)
{
	AdjTable temp;		

	temp = viceEulerPath;
	
	while(temp->next)	
		temp = temp->next;		 
	return temp->vertex == vertex;
}

// delete last vertex in the euler path
void deleteLastEuler(int vertex)
{
	AdjTable temp;		

	temp = viceEulerPath;
	
	if(!temp->next)
		return;
	while(temp->next->next)	
		temp = temp->next;	
	if(temp->next->vertex == vertex)
	{
		free(temp->next);
		temp->next = NULL;
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

void printEulerPath(AdjTable path)
{
	AdjTable temp;

	printf("\n\t === print euler path ===\n\t");

	temp = path;
	printf(" v[%d]", viceEulerPath->vertex+1);		
	while(temp->next)
	{
		printf("->v[%d]", temp->next->vertex+1);
		temp = temp->next;
	}
	
	printf("->v[%d]", viceEulerPath->vertex+1);
	printf("\n");
}

// delete edges consist of vertexed in euler path 
void deleteGraphByEuler()
{
	AdjTable temp;
	int vertex;
	int adjVertex;	

	temp = viceEulerPath;
	while(temp->next) // judge whether builded euler path has vertexes whose adjoining vertexes are not visited
	{	
		vertex = temp->vertex;
		adjVertex = temp->next->vertex;
		deleteAdj(adj, vertex, adjVertex);		
		temp = temp->next;
	}
	//deleting over
	printf("\n\t=== after deleting the edges between vertexes in euler path, graph is as follows:===\n");
	printAdjTable(adj, size); 
}

// update the arrays recording info for graph 
void resetArray()
{	
	int i;

	counter = 0;
	for(i=0; i<size; i++)
	{
		visited[i] = 0;
		vertexIndex[i] = -1;
		parent[i] = -1;
	}	
}