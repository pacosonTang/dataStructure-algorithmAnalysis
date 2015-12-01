#include <stdio.h>
#include <malloc.h>

#define Error(str) printf("\n\terror: %s\n", str)

void eval(int n)
{
	double* C;
	int i;	

	i = 0;
	C = (double*)malloc(sizeof(double) * (n+1));
	if(!C)
	{
		Error("failed eval, for out of space !");
		return ;
	}
	
	C[i] = 1.0;
	printf("\n\tc[%d]=%lf", i, C[i]);

	for(i=1; i<=n; i++)
	{
		C[i] = 2 * C[i-1] / i  + i;
		printf("\n\tc[%d]=%lf", i, C[i]);
		C[i] += C[i-1];
	}
}

int main()
{	
	eval(5);

	printf("\n");
	return 0;
}