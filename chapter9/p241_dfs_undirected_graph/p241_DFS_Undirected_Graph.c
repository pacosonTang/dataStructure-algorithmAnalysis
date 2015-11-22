#include "dfs.h" 

int *makeEmptyIntArray(int size, int firstValue); 

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
	start = 0; // startVertex is the startup we choose

	printf("\n\n\t ====== test for DFS applied into undirected graph ======\n");
	adj = initAdjTable(size);		
	visited = makeEmptyIntArray(size, 0);
	counter = 0;
	vertexIndex = makeEmptyIntArray(size, -1);
	parent = makeEmptyIntArray(size, -1);
	backsides = initAdjTable(size);

	printf("\n\n\t ====== the initial adjoining table is as follows:======\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])			
				insertAdj(adj, i, adjTable[i][j]-1); // insertAdj the adjoining table over
	
	printAdjTable(adj, size); 
	parent[start] = size;

	dfs(start);

	for(i=0; i<size; i++) 	 
		if(!visited[i]) // if the graph is not interconnected, we should conduct multiple DFS towards the graph
			dfs(i);	 
	
	printTraversalOrder();	
	printParentArray();
	printBacksides();

	printf("\n\n\t");

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