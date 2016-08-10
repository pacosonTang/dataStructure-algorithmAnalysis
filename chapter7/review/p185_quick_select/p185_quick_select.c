#include "p185_quick_select.h"

int main()
{
	ElementType array[] = {34, 8, 64, 51, 32, 21, 64, 8,
							35, 9, 65, 50, 31, 20, 63, 8};		 
	int size=16;    
	int k = 6;

	// test for quickselect.
	printf("\ntest for quickselect towards {34, 8, 64, 51, 32, 21, 64, 8, 35, 9, 65, 50, 31, 20, 63, 8}\n");
	quickselect(array, 0, size-1, k-1); // pass k-1 not k, you know it.
	printf("\nthe %dth maximum element is %d \n", k, array[k-1]);
}