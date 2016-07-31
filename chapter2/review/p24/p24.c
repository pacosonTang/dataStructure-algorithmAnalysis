#include<stdio.h>

int isEven(int N)
{
	return N % 2 == 0 ? 1 : 0;
}

long int pow(int x, int N)
{
    if(N == 0)
        return 1;
    if(N == 1)
        return x;
    if(isEven(N))    /* if(x) == if(N!=0) */
		return pow(x * x, N / 2);
    else
		return pow(x * x, N / 2) * x;
}

void main()
{
    int x = 2, N = 7;
    long pow_ = pow(x,N);
	printf("\t\t\t ========== test for computing pow  ==========\n");
	
    printf("\t\t\t result of %d^%d  is %-6d\n", x, N, pow_);
} 
