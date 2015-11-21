#include "undirected_graph.h" 

AdjTable* adj;		  
int *visited;
int size;

int *makeEmptyIntArray(int size, int firstValue);

//computing the unweighted shortest path between the vertex under initIndex and other vertexs
void dfs_undirected_graph(Vertex vertex)
{	
	AdjTable temp;
	Vertex adjVertex;

	visited[vertex] = 1;
	printf("\n\t visited[%d] = 1", vertex);
	temp = adj[vertex];
	while(temp->next)
	{
		adjVertex = temp->next->vertex;
		if(!visited[adjVertex])
			dfs_undirected_graph(adjVertex);
		temp = temp->next;
	}
	printf("\n\t");
}  

int main()
{ 

	int i;
	int j;
	int column ;	
	Vertex start;

	int adjTable[][3] = 
	{
		{2, 4, 5},
		{1, 3, 4},
		{2, 4, 5},
		{1, 2, 3},
		{1, 3, 0},		
	};	 
	size = 5;
	column = 3;
	start = 1; // startVertex is the startup we choose

	printf("\n\n\t ====== test for DFS applied into undirected graph ======\n");
	adj = initAdjTable(size);		
	visited = makeEmptyIntArray(size, 0);

	printf("\n\n\t ====== the initial adjoining table is as follows:======\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])			
				insertAdj(adj, i, adjTable[i][j]-1); // insertAdj the adjoining table over
	
	printAdjTable(adj, size); 
	
	dfs_undirected_graph(start-1);
	return 0;
} 


// allocate the memory for storing index of  vertex in heap and let every element -1
int *makeEmptyIntArray(int size, int firstValue)
{
	int *array;
	int i;

	array = (int*)malloc(size * sizeof(int));
	if(!array)
	{
		Error("out of space ,from func makeEmptyIntArray");
		return NULL;
	}		
	for(i=0; i<size; i++)
		array[i] = firstValue;

	return array;
}