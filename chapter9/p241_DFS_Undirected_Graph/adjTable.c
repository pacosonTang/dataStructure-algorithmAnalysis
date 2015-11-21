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

void insertAdj(AdjTable* table, int index, int adjVertex)
{
	AdjTable temp;
	AdjTable temp1;

	temp = makeEmptyAdj();
	if(!temp)
	{
		Error("failed insertAdj for out of space, from func insertAdj");
		return ;
	}
	temp->vertex = adjVertex; // create the AdjTablee with index over	

	temp1 = table[index];
	while(temp1->next)
		temp1 = temp1->next;
	 
	temp1->next = temp;			
}
 
void printAdjTable(AdjTable* link, int size)
{
	int i;
	AdjTable temp;

	for(i = 0; i < size; i++)
	{
		printf("\t adjoinLink[%d] ->", i);
		temp = link[i];
		while(temp->next)
		{
			printf(" vertex[%d] ->", temp->next->vertex);
			temp = temp->next;
		}
		printf(" NULL\n");
	}

	printf("\n\n");
}