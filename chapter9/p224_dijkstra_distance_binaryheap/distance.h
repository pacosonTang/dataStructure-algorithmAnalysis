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

// allocate the memory for Distance struct
Distance makeEmptyDistance()
{
	Distance element;

	element = (Distance)malloc(sizeof(struct Distance));
	if(!element)
	{
		Error("out of space ,from func makeEmptyDistance");
		return NULL;
	}		

	return element;
}
