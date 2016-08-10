#include "p173_merge_sort.h"

int main()
{	
	ElementType raw[] = {10, 100, 20, 90, 60, 50, 120, 140, 130, 5};
	int size = 10;
	
	ElementType *tempArray;					

	tempArray = createArray(size);
	if(tempArray==NULL)
	{
		return -1;
	}

	mergesort(raw, tempArray, 0, size-1);	
	printf("\nexecute mergesort for {10, 100, 20, 90, 60, 50, 120, 140, 130, 5}\n");		
	printArray(raw, size);	

	return 0;
}