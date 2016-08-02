#include "p165_insertion_sort.h"

int main()
{
	int length=9;
	int data[] = {100, 1000, 100, 10, 6, 2, 19, 25, 15};
	
	insertion_sort(data, length);
	printf("\n=== after executing insertion_sort === \n");
	printArray(data, length);	
}