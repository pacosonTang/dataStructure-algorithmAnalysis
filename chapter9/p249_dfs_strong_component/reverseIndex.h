#include <stdio.h>

struct ReverseIndex;
typedef struct ReverseIndex ReverseIndex;
typedef struct ReverseIndex* ReverseIndexPtr;

struct ReverseIndex
{
	int vertex;
	int reverse;
};
