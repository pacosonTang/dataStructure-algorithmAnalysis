#include <stdio.h>
 
#define Vertex int

struct Edge;
typedef struct Edge Edge;
typedef struct Edge* EdgePtr;
struct Edge
{
	Vertex start;
	Vertex end;
	int weight;	
};

EdgePtr makeEmptyElement();
EdgePtr *makeEmptyArray(int size);
