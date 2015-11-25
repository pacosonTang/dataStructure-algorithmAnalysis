#include "adjTable.h"

#define Error(str) printf("\n error: %s\n", str)

char flag[] = 
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G',
			'H', 'I', 'J', 'K', 'L', 'M', 'N',
			'O', 'P', 'Q', 'R', 'S', 'T',
			'U', 'V', 'W', 'X', 'Y', 'X'
		};
 
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

// delete the edge between vertex and adjVertex
void deleteAdj(AdjTable* table, int vertex, int adjVertex)
{
	AdjTable temp;
	AdjTable temp1;

	temp = table[vertex];
	while(temp->next)	 
	{
		if(temp->next->vertex == adjVertex)
		{
			temp1 = temp->next;
			temp->next = temp->next->next;
			free(temp1);
			break;
		}
		temp = temp->next;
	}	
	
	temp = table[adjVertex];
	while(temp->next)	 
	{
		if(temp->next->vertex == vertex)
		{
			temp1 = temp->next;
			temp->next = temp->next->next;
			free(temp1);
			break;
		}
		temp = temp->next;
	}	
}

 
void printAdjTable(AdjTable* link, int size)
{
	int i;	
	AdjTable temp;		

	for(i = 0; i < size; i++)
	{
		printf("\t v[%d] ->", i+1);
		temp = link[i];
		while(temp->next)
		{
			printf(" v[%d] ->", temp->next->vertex + 1);
			temp = temp->next;
		}
		printf(" NULL\n");
	}	
}