#include <stdio.h>
#include <malloc.h>

#define Vertex int

struct AdjTable;
typedef struct AdjTable* AdjTable;

struct AdjTable
{
	int vertex;
	AdjTable next;	
	int visited;
};

AdjTable* initAdjTable(int size);
AdjTable makeEmptyAdj();
void printAdjTable(AdjTable* link, int size);
void insertAdj(AdjTable*, int vertex, int adjVertex);
void deleteAdj(AdjTable*, int vertex, int adjVertex);
