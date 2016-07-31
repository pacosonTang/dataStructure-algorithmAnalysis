#include<stdio.h>

#define ElementType int
#define NOTFOUND -1

/* 求两个数的最大公因数（greatest common divisor） */
int gcd(int M, int N)
{
    int rem;

    printf("remainder sequence: ");
    while (N > 0)
    {
        rem = M % N;
        M = N;
        N = rem;
        printf("%4d", rem);
    }
    return M;
}

main()
{
    int N = 1989, M = 1590;    
	int gcd_value;

	printf("\t\t\t ========== test for greatest common divisor ==========\n\n");
    
    gcd_value = gcd(M, N);
    printf("\nthe greatest common divisor between %4d and %4d is %4d\n", M, N, gcd_value);

}