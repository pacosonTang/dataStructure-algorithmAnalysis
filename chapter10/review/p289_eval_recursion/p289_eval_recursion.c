#include <stdio.h>
#include <malloc.h>

#define Error(str) printf("\n\terror: %s\n", str)

void eval(int n)
{
	double* array;
	int i;	

	i = 0;
	array = (double*)malloc(sizeof(double) * (n+1));
	if(array == NULL)
	{
		Error("failed eval, for out of space !");
		return ;
	}
	
	array[i] = 1.0;
	printf("\n\tarray[%d] = %8lf", i, array[i]);

	for(i=1; i<=n; i++)
	{
		array[i] = 2 * array[i-1] / i  + i;
		printf("\n\tarray[%d] = %8lf", i, array[i]);
		array[i] += array[i-1];
	}
}

int main()
{	
	eval(5);

	printf("\n");
	return 0;
}