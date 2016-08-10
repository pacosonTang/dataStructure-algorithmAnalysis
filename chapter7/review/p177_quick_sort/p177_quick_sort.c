#include "p177_quick_sort.h"

int main()
{
	ElementType array[] = {34, 8, 64, 51, 32, 21, 64, 8,
						   33, 9, 63, 52, 31, 20, 63, 9};

	ElementType array2[] = {34, 8, 64, 51, 32, 21, 64, 8};
	ElementType array3[] = {34, 8, 64, 51, 32, 21, 64, 8};
	int size=16;    
	
	// test for quicksort.
	printf("\ntest for quicksort towards {34, 8, 64, 51, 32, 21, 64, 8, 33, 9, 63, 52, 31, 20, 63, 9}\n");
	quicksort(array, 0, size-1);
	printArray(array, size);	
	
	size=8;
	// test for median3
	printf("\ntest for median3 towards {34, 8, 64, 51, 32, 21, 64, 8}\n");
	median3(array2, 0, size-1);
	printArray(array2, size);

	// test for insertionSort
	printf("\ntest for insertionSort towards {34, 8, 64, 51, 32, 21, 64, 8}\n");
	insertionSort(array3, 0, size-1);
	printArray(array3, size);
}