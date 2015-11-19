#include "adjTable.h"
#include <math.h>
#include "binaryHeap.h"

#define MaxInt (int)pow(2, 16)

struct WeightedTable;
typedef struct WeightedTable* WeightedTable;

struct WeightedTable
{
	int known;
	int distance;
	int path;
};

WeightedTable makeEmptyWeightedTable();
WeightedTable *initWeightedTable(int size);
void dijkstra(AdjTable* adj, int size, int initIndex, BinaryHeap bh);
void printDijkstra(WeightedTable* table, int size, int startVertex);