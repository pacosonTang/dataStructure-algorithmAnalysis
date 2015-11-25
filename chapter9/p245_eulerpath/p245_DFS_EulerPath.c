#include "dfs.h" 

int *makeEmptyIntArray(int size, int firstValue); 

int main()
{ 

	int i;
	int j;
	int column ;
	AdjTable temp;	
	 
	int adjTable[][6] = 
	{
		{3, 4, 0, 0, 0, 0}, //1
		{3, 8, 0, 0, 0, 0}, //2
		{1, 2, 4, 6, 7, 9}, //3
		{1, 3, 5, 7, 10, 11}, //4
		{4, 10, 0, 0, 0, 0}, //5
		{3, 9, 0, 0, 0, 0}, //6
		{3, 4, 9, 10, 0, 0}, //7
		{2, 9, 0, 0, 0, 0}, //8
		{3, 6, 7, 8, 10, 12}, //9
		{4, 5, 7, 9, 11, 12}, //10
		{4, 10, 0, 0, 0, 0}, //11
		{9, 10, 0, 0, 0, 0}, //12
	};
 

	size = 12;
	column = 6;
	start = 4; // startVertex is the startup we choose ,whose index starts from 1

	printf("\n\n\t ====== test for DFS finding Euler Path from the given graph======\n");
	adj = initAdjTable(size);		
	visited = makeEmptyIntArray(size, 0);
	counter = 0;
	vertexIndex = makeEmptyIntArray(size, -1);
	parent = makeEmptyIntArray(size, -1);		

	printf("\n\n\t ====== the initial adjoining table is as follows:======\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])			
				insertAdj(adj, i, adjTable[i][j]-1); // insertAdj the adjoining table over
	
	printAdjTable(adj, size); 
	parent[start] = size;
	
	printf("\n\t=== results of conducting DFS towards the given graph ===\n");
	visitFlag = 0;
	dfs(start, 1);
	for(i=0; i<size; i++) 	 
	{
		if(!visited[i]) // if the graph is not interconnected, we should conduct multiple DFS towards the graph
		{
			start = i;
			dfs(start, 1);	 					
		}
	}	
	
	printf("\n\t=== results of conducting DFS to find Euler path from the given graph ===\n");
	
	/*counter = 0;
	for(i=0; i<size; i++)
	{
		visited[i] = 0;
		vertexIndex[i] = -1;
		parent[i] = -1;
	}*/		

	visitFlag = 0;
	viceEulerPath = makeEmptyAdj();
	viceEulerPath->vertex = start;		
	resetArray(); // reset arrays to conduct new dfs again	
	findEulerPath(start, 1);// conducting first dfs to find the euler path
	
	printEulerPath(viceEulerPath); // print euler path		 	
	deleteGraphByEuler(); // delete edges whose vertexes in the euler path	
	
	mainEulerPath = viceEulerPath;
	// conducting other dfs to find euler path
	temp = viceEulerPath;
	while(temp->next) // judge whether builded euler path has vertexes whose adjoining vertexes are not visited
	{		
		start = temp->next->vertex;
		if(hasAdjVertex(start)) // judge whether the start vertex has adjoining vertexes or not
		{
			visitFlag = 0;
			viceEulerPath = makeEmptyAdj();
			viceEulerPath->vertex = start; // initializing viceEulerPath over
			
			resetArray(); // reset arrays to conduct new findEulerPath again
			findEulerPath(start, 1);
			printEulerPath(viceEulerPath); // print euler path		 	
			deleteGraphByEuler(); // delete edges whose vertexes in the euler path
		}
		temp = temp->next;
	}	
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

 