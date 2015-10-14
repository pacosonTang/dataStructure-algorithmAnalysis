#include<stdio.h>

#define ElementType int

int maxSubsequenceSum(int A[], int N)
{
    int thisSum, maxSum, i, j;

    maxSum = 0;
    for(i = 0; i < N; i++) 
	{ 
        thisSum = 0;
        for(j = i; j < N; j++) 
		{    /* i划分出两个集合，j from i to N-1 */
            thisSum += A[j];                            
            if(thisSum > maxSum)
                maxSum = thisSum;
        }     
    }
    return maxSum;
}

/* 打印数组数据 */
void printArray(int* a, int N)
{
    for(int i = 0; i < N; i++)
        printf("%4d", a[i]);
    printf("\n");
}

main()
{
    int N = 8, maxSum = 0;    
    char p[256];
    char *str = p;
    ElementType A[] = {4, -3, 5, -2, -1, 2, 6, -2};

    printf("\t\t\t ========== [second method] test for maximum sum of subsequence ==========\n\n");
    str = "initial array A: ";
    printf("%50s",str);
    printArray(A, N);    

    str = "after computing maximum sum of subsequence: ";
    printf("%50s", str);
    maxSum = maxSubsequenceSum(A, N);
    printArray(A, N);

    str = "the maximum sum of array subsequence is: ";
    printf("%50s", str);
    printf("%4d\n\n", maxSum);

    return 0;
}
