#include <stdio.h>

#define Error(str) printf("\n error: %s \n",str)   

struct Distance;
typedef struct Distance *Distance;
struct Distance
{
	int vertexIndex;
	int distance;
};

Distance makeEmptyDistance();


