#include "p167_shell_sort.h"

int main()
{		
	int array[] = {100, 1000, 100, 10, 6, 2, 19, 25, 15, 55, 
				   35, 5, 110, 120, 119};
	int length = 15;	
	
	shell_sort(array, length);
	printArray(array, length);
}