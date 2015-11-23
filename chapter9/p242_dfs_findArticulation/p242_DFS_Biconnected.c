#include "dfs.h" 

int *makeEmptyIntArray(int size, int firstValue);
extern char flag[];

int main()
{ 
	int i;
	int j;
	int column ;		

	int adjTable[][4] = 
	{
		{2, 4, 0, 0},
		{1, 3, 0, 0},
		{2, 4, 7, 0},
		{1, 3, 5, 6},
		{4, 6, 0, 0},
		{4, 5, 0, 0},
		{3, 0, 0, 0},
	};	 
	size = 7;
	column = 4;
	start = 0; // startVertex is the startup we choose

	printf("\n\n\t ====== test for DFS finding articulation point from the given graph ======\n");
	adj = initAdjTable(size);		
	visited = makeEmptyIntArray(size, 0);
	counter = 0;
	vertexIndex = makeEmptyIntArray(size, -1);
	vertexLow = makeEmptyIntArray(size, -1);
	parent = makeEmptyIntArray(size, -1);	

	printf("\n\t === the initial adjoining table is as follows:===\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])			
				insertAdj(adj, i, adjTable[i][j]-1); // insertAdj the adjoining table over
	
	parent[start] = size;
	printAdjTable(adj, size); 
		
	printf("\n\t=== results of conducting DFS to find articulation point ===\n");
	findArticulate(start, 1); // start to conduct dfs for the given graph
	for(i=0; i<size; i++) 	 
	{
		if(!visited[i]) // if the graph is not interconnected, we should conduct multiple DFS towards the graph
			findArticulate(i, 1);		 
	}
	
	// judge whether the vertex start is the articulation point or not
	if(isStartArticulation())
		printf("\n\t vertex[%c] proves to be an articulation point !", flag[start]);
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