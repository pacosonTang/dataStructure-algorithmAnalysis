#include "dijkstra.h"

//allocate the memory for initializing unweighted table
WeightedTable *initWeightedTable(int size)
{	
	WeightedTable* table;
	int i;

	table = (WeightedTable*)malloc(sizeof(WeightedTable) * size);
	if(!table)
	{
		Error("out of space ,from func initWeightedTable");
		return NULL;
	}

	for(i = 0; i < size; i++)
	{
		table[i] = makeEmptyWeightedTable();		
		if(!table[i])
			return NULL;
	}

	return table;
} 

// allocate the memory for every element in unweighted table  
WeightedTable makeEmptyWeightedTable()
{
	WeightedTable element;

	element = (WeightedTable)malloc(sizeof(struct WeightedTable));
	if(!element)
	{
		Error("out of space ,from func makeEmptyWeightedTable");
		return NULL;
	}	
	element->known = 0; // 1 refers to accessed , also 0 refers to not accessed
	element->distance = MaxInt;
	element->path = -1; // index starts from 0 and -1 means the startup vertex unreaches other vertexs

	return element;
}

// allocate the memory for storing index of  vertex in heap and let every element -1
int *makeEmptyArray(int size)
{
	int *array;
	int i;

	array = (int*)malloc(size * sizeof(int));
	if(!array)
	{
		Error("out of space ,from func makeEmptyArray");
		return NULL;
	}		
	for(i=0; i<size; i++)
		array[i] = -1;

	return array;
}

//computing the unweighted shortest path between the vertex under initIndex and other vertexs
void dijkstra(AdjTable* adj, int size, int startVertex, BinaryHeap bh)
{		
	int adjVertex;	
	int tempDistance;
	WeightedTable* table;
	int vertex;		
	AdjTable temp; 	
	Distance tempDisStruct;
	int *indexOfVertexInHeap;
	int indexOfHeap;

	table = initWeightedTable(size);	 	
	tempDisStruct = makeEmptyDistance();
	indexOfVertexInHeap = makeEmptyArray(size);
	
	tempDisStruct->distance = table[startVertex-1]->distance;
    tempDisStruct->vertexIndex = startVertex-1;
	insert(tempDisStruct, bh, indexOfVertexInHeap); // insert the (startVertex-1) into the binary heap	

	table[startVertex-1]->distance = 0;// update the distance 
	table[startVertex-1]->path = 0;// update the path of starting vertex

	while(!isEmpty(bh))
	{
		//vertex = deQueue(queue); // if the queue is not empty, conducting departing queue 
		vertex = deleteMin(bh, indexOfVertexInHeap).vertexIndex; // return the minimal element in binary heap
		
		table[vertex]->known = 1; // update the vertex as accessed, also responding known 1
		temp = adj[vertex]->next;
		while(temp)
		{
			adjVertex = temp->index; // let each adjVertex adjacent to vertex enter the queue
			
			//enQueue(queue, adjVertex); 
			tempDistance = table[vertex]->distance + temp->weight; // update the distance
			if(tempDistance < table[adjVertex]->distance)
			{
				table[adjVertex]->distance = tempDistance;
				table[adjVertex]->path = vertex; //update the path of adjVertex, also responding path evaluated as vertex							
				
				// key, we should judge whether adjVertex was added into the binary heap				
				//if true , obviously the element has been added into the binary heap(so we can't add the element into heap once again)
				if(indexOfVertexInHeap[adjVertex] != -1) 
				{
					indexOfHeap = indexOfVertexInHeap[adjVertex];
					bh->elements[indexOfHeap]->distance = tempDistance; // update the distance of corresponding vertex in binary heap
				}
				else 
				{
					tempDisStruct->distance = table[adjVertex]->distance;
					tempDisStruct->vertexIndex = adjVertex;
					insert(tempDisStruct, bh, indexOfVertexInHeap); // insert the adjVertex into the binary heap
				}
			}			 
			temp = temp->next;		
		}		
		printDijkstra(table, size, startVertex);		
		printBinaryHeap(bh);
		printf("\n");
	}		
	
	printf("\n");
} 

//print unweighted table
void printDijkstra(WeightedTable* table, int size, int startVertex)
{
	int i;	
	char *str[4] = 
	{
		"vertex",
		"known",
		"distance",
		"path"
	};

	printf("\n\t === storage table related to Dijkstra alg as follows: === ");	
	printf("\n\t %6s%6s%9s%5s", str[0], str[1], str[2], str[3]);	
	for(i=0; i<size; i++)
	{		
		if(i != startVertex-1 && table[i]->path!=-1) 
			printf("\n\t %-3d   %3d   %5d      v%-3d  ", i+1, table[i]->known, table[i]->distance, table[i]->path+1);
		else if(table[i]->path == -1)
			printf("\n\t %-3d   %3d   %5d      %-3d  ", i+1, table[i]->known, table[i]->distance, table[i]->path);
		else
			printf("\n\t *%-3d  %3d   %5d      %-3d  ", i+1, table[i]->known, table[i]->distance, 0);
	}	 
}

int main()
{ 
	AdjTable* adj;	
	BinaryHeap bh;
	int size = 7;
	int capacity;
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
	
	int weight[7][7] = 
	{
		{2, 1, 0, 0},
		{3, 10, 0, 0},
		{4, 5, 0, 0},
		{2, 2, 8, 4},
		{6, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 0, 0, 0}
	};

	printf("\n\n\t ====== test for dijkstra alg finding weighted shortest path from adjoining table ======\n");
	adj = initAdjTable(size);		
	
	printf("\n\n\t ====== the initial weighted adjoining table is as follows:======\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])			
				insertAdj(adj, adjTable[i][j]-1, i, weight[i][j]); // insertAdj the adjoining table over
	
	printAdjTable(adj, size);
	
	capacity = 7;
	bh = initBinaryHeap(capacity+1);
	//conducting dijkstra alg to find the unweighted shortest path starts	
	startVertex = 1; // you should know our index for storing vertex starts from 0
	dijkstra(adj, size, startVertex, bh);
	
	return 0;
} 
