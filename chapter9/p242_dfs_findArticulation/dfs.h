#include "adjTable.h"

#define Error(str) printf("\n\t %s \n", str)
#define Vertex int

void dfs(Vertex vertex, int);
void printTraversalOrder();
void printParentArray();
void printBacksides();

void assignIndex(Vertex vertex); // assign visited indexes for the vertexes
void findArticulate(Vertex vertex, int); // find the articulation point from the given graph
int isStartArticulation(); // judge whether the start is the articulation point or not, also 1 or 0

AdjTable* adj;		  
int *visited;
int size;
int counter;
Vertex start;
int *vertexIndex; // recording traversal sequence for the vertexes
int *vertexLow; // recording low value of vertex
int *parent; // recoding the parent of the vertex 
