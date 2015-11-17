#include "unweightedTable.h"

// allocate the memory for every element in unweighted table  
UnweightedTable makeEmptyUnweightedTable()
{
	UnweightedTable element;

	element = (UnweightedTable)malloc(sizeof(struct UnweightedTable));
	if(!element)
	{
		Error("out of space ,from func makeEmptyUnweightedTable");
		return NULL;
	}	
	element->known = 0; // 1 refers to accessed , also 0 refers to not accessed
	element->distance = MaxInt;
	element->path = -1; // index starts from 0

	return element;
}

//allocate the memory for initializing unweighted table
UnweightedTable *initUnweightedTable(int size)
{	
	UnweightedTable* table;
	int i;

	table = (UnweightedTable*)malloc(sizeof(UnweightedTable) * size);
	if(!table)
	{
		Error("out of space ,from func initUnweightedTable");
		return NULL;
	}

	for(i = 0; i < size; i++)
	{
		table[i] = makeEmptyUnweightedTable();		
		if(!table[i])
			return NULL;
	}

	return table;
} 

//computing the unweighted shortest path between the vertex under initIndex and other vertexs
void unweighted_shortest_path(AdjTable* adj, int size, int startVertex, Queue queue)
{		
	int adjVertex;	
	UnweightedTable* table;
	ElementType vertex;		
	AdjTable temp; 
	
	table = initUnweightedTable(size);	 

	enQueue(queue, startVertex-1); //if let start vertex equals to v3, then initIndex=3 and let index=2 enter the queue	 	
	table[startVertex-1]->distance = 0;// update the distance 
	table[startVertex-1]->path = 0;// update the path of starting vertex

	while(!isEmpty(queue))
	{
		vertex = deQueue(queue); // if the queue is not empty, conducting departing queue 	
		table[vertex]->known = 1; // update the vertex as accessed, also responding known 1

		temp = adj[vertex]->next;
		while(temp)
		{
			adjVertex = temp->index; // let each adjVertex adjacent to vertex enter the queue
			if(table[adjVertex]->path == -1) // key that judge whether corresponding element's path equals to -1 ,-1 means the element has never entered the queue
			{
				enQueue(queue, adjVertex); 
				table[adjVertex]->distance = table[vertex]->distance + 1;// update the distance 
				table[adjVertex]->path = vertex; //update the path of adjVertex, also responding path evaluated as vertex
			}
			temp = temp->next;		
		}										
	}
	
	disposeQueue(queue);
	//print unweighted table
	printUnweightedtable(table, size, startVertex);

	printf("\n\t");
} 

//print unweighted table
void printUnweightedtable(UnweightedTable* table, int size, int startVertex)
{
	int i;
	int path;
	char *str[4] = 
	{
		"vertex",
		"known",
		"distance",
		"path"
	};

	printf("\n\t unweighted shortest path table are as follows:\n");	
	printf("\n\t %6s%6s%9s%5s", str[0], str[1], str[2], str[3]);	
	for(i=0; i<size; i++)
	{		
		if(i != startVertex-1) 				
			printf("\n\t %-3d   %3d   %5d      v%-3d  ", i+1, table[i]->known, table[i]->distance, table[i]->path+1);
		else
			printf("\n\t *%-3d  %3d   %5d      %-3d  ", i+1, table[i]->known, table[i]->distance, 0);
	}	 
}

int main()
{ 
	AdjTable* adj;		
	Queue queue;
	int size = 7;
	int i;
	int j;
	int column = 4;
	int startVertex;

	int adjTable[7][4] = 
	{
		{2, 4, 0, 0},
		{4, 5, 0, 0},
		{1, 6, 0, 0},
		{3, 5, 6, 7},
		{7, 0, 0, 0},
		{0, 0, 0, 0},
		{6, 0, 0, 0}
	};
	
	printf("\n\n\t ====== test for topological sorting with adjoining table ======\n");
	adj = initAdjTable(size);	
	queue = initQueue(size);
	
	printf("\n\n\t ====== the initial adjoining table is as follows:======\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])			
				insertAdj(adj, adjTable[i][j]-1, i); // insertAdj the adjoining table over							 
	
	printAdjTable(adj, size);
	
	// finding the unweighted shortest path starts	
	// void unweighted_shortest_path(AdjTable* adj, int size, int initIndex, Queue queue)
	startVertex = 3; // we set the vertex3 as the start vertex (but you know, whose index in array is 2)
	unweighted_shortest_path(adj, size, startVertex, queue);
	
	return 0;
} 