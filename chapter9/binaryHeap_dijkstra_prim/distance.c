#include "distance.h"
#include <malloc.h>

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
