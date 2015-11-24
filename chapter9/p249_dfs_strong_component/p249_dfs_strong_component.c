#include "dfs.h" 

int *makeEmptyIntArray(int size, int firstValue); 

int main()
{ 

	int i;
	int j;
	int column ;
	Vertex tempVertex;
	int *traversalSeq; // recording vertexes of dfs traversal sequence 	
	int seqSize;

	int adjTable[][3] = 
	{
		{2, 4, 0},//A
		{3, 6, 0},//B
		{1, 4, 5},//C
		{5, 0, 0},//D
		{0, 0, 0},//E
		{3, 0, 0},//F
		{6, 8, 0},//G
		{6, 10, 0},//H
		{8, 0, 0},//I
		{9, 0, 0},//J
	};
	size = 10;
	column = 3;
	start = 1; // startVertex is the startup we choose

	printf("\n\n\t ====== test for DFS traversing directed graph ======\n");
	adj = initAdjTable(size);
	reverseAdj = initAdjTable(size);
	visited = makeEmptyIntArray(size, 0);
	traversalSeq = makeEmptyIntArray(size, -1);
	counter = 0;
	reverseCounter = 0;
	vertexIndex = makeEmptyIntArray(size, -1);
	reverseVertexIndex = makeEmptyIntArray(size, -1);
	parent = makeEmptyIntArray(size, -1);	
	
	// initializing the binary heap for finding strong component from reverse graph	
	bh = initBinaryHeap(20);

	printf("\n\n\t ====== the initial adjoining table is as follows:======\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])			
				insertAdj(adj, i, adjTable[i][j]-1); // insertAdj the adjoining table over
	
	printAdjTable(adj, size); 
	parent[start] = size;

	printf("\n\t=== results of conducting DFS towards the given directed graph ===\n"); 
	printf("\t=== judging whether the given directed graph has a circle , also has backsides or not===\n"); 
	dfs(start, 1);
	for(i=0; i<size; i++)
	{
		if(!visited[i]) // if the graph is not interconnected, we should conduct multiple DFS towards the graph	
		{
			start = i;
			dfs(start, 1);	 					 
		}
	}
	
	//print reverse vertex index
	printVertexIndex(reverseVertexIndex, size);	
	
	printf("\n\n\t === the reverse graph of given directed graph is as follows:===\n");
	printAdjTable(reverseAdj, size);	
	
	// conducting dfs for the reverse graph to find the strong component		
	printf("\n\n\t === the binary heap storing reverse index of reverse graph ===");
	printBinaryHeap(bh);
	
	// test of dfs traversing the reverse graph, using binary heap
	printf("\n\n\t === test of dfs traversing the reverse graph ===\n");	
	counter = 0;
	for(i=0; i<size; i++)
	{
		visited[i] = 0;
		vertexIndex[i] = -1;
		parent[i] = -1;
	}	
	
	i = 0;
	while(!isEmpty(bh))
	{
		tempVertex = deleteMax(bh).vertex;		
		if(!visited[tempVertex]) {
			traversalSeq[i++] = tempVertex;
			strongComponent(tempVertex, 1);
		}
	}	
	seqSize = i;
	// over
	
	// sets of dfs traversal procedure above 
	printf("\n\t=== sets of dfs traversal procedure above ==="); 
	counter = 0;
	for(i=0; i<size; i++)
	{
		visited[i] = 0;
		vertexIndex[i] = -1;
		parent[i] = -1;
	}	
	
	start = traversalSeq[0];
	dfsPathSet(start, 1);
	for(i=1; i<seqSize; i++)
	{
		start = traversalSeq[i];		
		dfsPathSet(start, 1);	 					 		 
	}
	// over

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

