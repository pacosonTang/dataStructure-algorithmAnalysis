#include <stdio.h>
#include <malloc.h>

struct AdjTable;
typedef struct AdjTable* AdjTable;

struct AdjTable
{
	int vertex;
	AdjTable next;	
};

AdjTable* initAdjTable(int size);
AdjTable makeEmptyAdj();
void printAdjTable(AdjTable* link, int size);
void insertAdj(AdjTable*, int, int);
void deleteAdj(AdjTable* table, int index, int adjVertex);
