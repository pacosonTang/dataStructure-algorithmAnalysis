#include "adjTable.h"
#include "queue.h" 

void topSort(AdjTable* adj, int size, int* indegreeArray, Queue queue)
{
	int i;
	int counter;
	ElementType vertex;	
	ElementType adjVertex;
	AdjTable temp;
	AdjTable temp1;
	
	for(i=0; i<size; i++)
		if(!indegreeArray[i]) // find the element who has zero indegree in adjoining table	
			enQueue(queue, i); //let the element enter the queue
	
	printf("\t topSorting sequence is as follows: ");
	counter = 0;

	while(!isEmpty(queue))
	{
		vertex = deQueue(queue); // if the queue is empty, conducting departing queue
		temp = adj[vertex]->next;
		while(temp)
		{
			adjVertex = temp->index; // each adjVertex adjacent to vertex			
			if(--indegreeArray[adjVertex] == 0)			 
				enQueue(queue, adjVertex);	
			 
			temp1 = temp->next;
			free(temp);
			temp = temp1;						
		}			
		printf("vertex[%d]  ", vertex+1);
		counter++;
	}
	if(counter != size)
		Error("failed top sorting, for graph has a cycle, from func topSort !");

	disposeQueue(queue);
	printf("\n\t");
}

// initializing indegree array with given size
int *initIndegree(int size)
{
	int *indegreeArray;
	int i;

	indegreeArray = (int*)malloc(sizeof(int) * size);
	
	if(!indegreeArray)
	{
		Error("failed intialization ,for out of space ,from func initIndegree");
		return NULL;
	}
	
	for(i=0; i < size; i++)
		indegreeArray[i] = 0;

	return indegreeArray;
}

int main()
{ 
	AdjTable* adj;
	int *indegreeArray;
	Queue queue;
	int size = 7;
	int i;
	int j;
	int column = 3;

	int adjTable[7][3] = 
	{
		{2, 4, 3},
		{4, 5, 0},
		{6, 0, 0},
		{6, 7, 3},
		{4, 7, 0},
		{0, 0, 0},
		{6, 0, 0}
	};
	
	printf("\n\n\t ====== test for topological sorting with adjoining table ======\n");
	adj = initAdjTable(size);
	indegreeArray = initIndegree(size);
	queue = initQueue(size);

	printf("\n\n\t ====== the initial adjoining table is as follows:======\n");
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjTable[i][j])
			{
				insertAdj(adj, adjTable[i][j]-1, i); // insertAdj the adjoining table over
				indegreeArray[adjTable[i][j]-1]++; // update indegree of elements
			}
	
	printAdjTable(adj, size);
	
	// topSorting starts	
	//void topSort(AdjTable* adj, int size, int* indegreeArray, Queue queue)
	topSort(adj, size, indegreeArray, queue);
	
	return 0;
} 