#include "adjTable.h"

#define Error(str) printf("\n\t %s \n", str)
#define Vertex int

void dfs(Vertex vertex, int);
void findEulerPath(Vertex vertex, int depth);
void buildEuler(Vertex vertex); // add vertex into the euler path by allocate memory to store it
int hasAdjVertex(Vertex vertex); // judge whether the adjoining vertex of giben vertex  was visited or not , also return index unvisited vertex or -1;
void printEulerPath(AdjTable);
void deleteLastEuler();
int isVertexInPath(Vertex vertex);
void deleteGraphByEuler();
void resetArray();

AdjTable* adj;
AdjTable mainEulerPath;
AdjTable viceEulerPath;
int *visited;
int size;
int counter;
int *vertexIndex; // recording traversal sequence for the vertexes
int *vertexLow; // recording low value of vertex
int *parent; // recoding the parent of the vertex 
Vertex start;
int visitFlag;

