#include "dfs.h"

extern char flag[];
//extern ElementTypePtr makeHeapNode();

// get the reverse graph and vertex index by postorder traversal
void dfs(Vertex vertex, int depth)
{
	int i;
	int visitFlag;
	AdjTable temp;
	Vertex adjVertex;
	ElementTypePtr heapnode;
	
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
				parent[adjVertex] = vertex; // building back side, attention of condition of building back side above
				
				// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("      ");
				printf("  v[%c]->v[%c] (backside) \n", flag[vertex], flag[adjVertex]);
			}			
		}
		
		//if(!visited[adjVertex])
		else
		{
			//if(vertex == start)
			//	visitFlag = 1;
			parent[adjVertex] = vertex;
			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("      ");			
			printf("  v[%c]->v[%c] (building edge) \n", flag[vertex], flag[adjVertex]);
			dfs(adjVertex, depth+1);			
		}
		// reverse the graph
		insertAdj(reverseAdj, adjVertex, vertex);				
		// reversing over

		//if(vertex == start && visitFlag) //conducingt dfs for only one adjoining vertex in the given graph
		//	break;	
		//if(!temp->next)
		//	break;
		temp = temp->next;			
	} 	
	reverseVertexIndex[vertex] = reverseCounter; // evaluating reverse vertex index when conduting post order	
	heapnode = makeHeapNode();
	heapnode->vertex = vertex;
	heapnode->reverse = reverseCounter++;	

	insertHeap(heapnode, bh); // insert the reverse index into the binary heap
} 

// finding the strong component from the reverse graph and strongComponent derives from dfs
void strongComponent(Vertex vertex, int depth)
{
	int i;
	AdjTable temp;
	Vertex adjVertex;	
	
	//printf("\n\t visited[%c] = 1 ", flag[vertex]);
	visited[vertex] = 1; // update visited status of vertex
	vertexIndex[vertex] = counter++; // number the vertex with counter
	temp = reverseAdj[vertex];	
		
	while(temp->next)
	{
		printf("   ");
		adjVertex = temp->next->vertex;		
		if(visited[adjVertex]) // judge whether the adjVertes was visited before		
		{
			if(vertexIndex[vertex] > vertexIndex[adjVertex] && parent[vertex] != adjVertex) 	
			{
				parent[adjVertex] = vertex; // building back side, attention of condition of building back side above
				
				// just for printing effect
				for(i = 0; i < depth; i++)  
					printf("      ");
				printf("v[%c]->v[%c] (backside) \n", flag[vertex], flag[adjVertex]);
			}
		}
		
		else
		{
			parent[adjVertex] = vertex;
			
			// just for printing effect
			for(i = 0; i < depth; i++)  
				printf("      ");
			printf("v[%c]->v[%c] (building edge)\n", flag[vertex], flag[adjVertex]);			
			strongComponent(adjVertex, depth+1);
		}		
		temp = temp->next;		
	} 	
}

// print vertex index
void printVertexIndex(int* array, int size)
{
	int i;
	printf("\n\t === reverse vertexIndex array is as follows: ===");
	for(i=0; i<size; i++)	 
		printf("\n\t reverseVertexIndex[%c] = %d", flag[i], array[i] + 1);	 
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
	temp = reverseAdj[vertex];	
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

