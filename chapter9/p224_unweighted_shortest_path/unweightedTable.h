#include "adjTable.h"
#include "queue.h" 
#include <math.h>

#define MaxInt (int)pow(2, 16)

struct UnweightedTable;
typedef struct UnweightedTable* UnweightedTable;

struct UnweightedTable
{
	int known;
	int distance;
	int path;
};

UnweightedTable makeEmptyUnweightedTable();
UnweightedTable *initUnweightedTable(int size);
void unweighted_shortest_path(AdjTable* adj, int size, int initIndex, Queue queue);
void printUnweightedtable(UnweightedTable* table, int size, int startVertex);