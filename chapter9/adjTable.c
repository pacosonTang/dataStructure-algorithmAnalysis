#include "adjTable.h"

#define Error(str) printf("\n error: %s\n", str)

// initilizing the adjoining link with size
AdjTable* initAdjTable(int size)
{
	AdjTable* adjTable;
	int i;

	adjTable = (AdjTable*)malloc(sizeof(AdjTable) * size);
	if(!adjTable)
	{
		Error("out of space ,from func intiAdjTable");
		return NULL;
	}

	for(i = 0; i < size; i++)
	{
		adjTable[i] = makeEmptyAdj();		
		if(!adjTable[i])
			return NULL;
	}

	return adjTable;
} 

// allocate the memory for the new node 
AdjTable makeEmptyAdj()
{
	AdjTable temp;

	temp = (AdjTable)malloc(sizeof(struct AdjTable));
	if(!temp)
	{
		Error("out of space ,from func makeEmptyAdj");
		return NULL;
	}	
	temp->next = NULL;

	return temp;
}

void insertAdj(AdjTable* link, int index, int start)
{
	AdjTable temp;
	AdjTable temp1;

	temp = makeEmptyAdj();
	if(!temp)
	{
		Error("failed insertAdj for out of space, from func insertAdj");
		return ;
	}
	temp->index = index; // create the AdjTablee with index over

	temp1 = link[start];
	while(temp1->next)
		temp1 = temp1->next;
	 
	temp1->next = temp;			
}

/*
int main()
{ 
	AdjTable* link;
	int size = 7;
	int i;
	int j;
	int column = 3;

	int adjArray[7][3] = 
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
	link = initAdjTable(size);
		
	for(i = 0; i < size; i++)
	 	for(j = 0; j < column; j++)	
			if(adjArray[i][j])
				insertAdj(link, adjArray[i][j]-1, i);		 	
				// insertAdj the adjoining table over
	
	printAdjTable(link, size);

	return 0;
} 
*/

void printAdjTable(AdjTable* link, int size)
{
	int i;
	AdjTable temp;

	for(i = 0; i < size; i++)
	{
		printf("\t adjoinLink[%d] -> ", i+1);
		temp = link[i];
		while(temp->next)
		{
			printf(" adjoinLink[%d] -> ", temp->next->index+1);
			temp = temp->next;
		}
		printf("NULL\n");
	}

	printf("\n\n");
}