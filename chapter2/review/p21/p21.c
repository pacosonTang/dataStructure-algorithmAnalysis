#include<stdio.h>

#define ElementType int

// 联机算法计算最大子序列和问题.
int maxSubSequenceSum(int A[], int N)
{
    int thisSum=0, maxSum=0;
	int j;    

    for(j = 0; j < N; j++) 
	{
        thisSum += A[j];
        if(thisSum > maxSum)
		{
            maxSum = thisSum;
		}
        else if(thisSum < 0)
		{
            thisSum = 0;
		}
    }
    return maxSum;
}

int main()
{
    int N = 8, maxSum = 0;            
    ElementType A[] = {4, -3, 5, -2, -1, 2, 6, -2};                    
    
	maxSum = maxSubSequenceSum(A, N);
    printf("the maximum sum of array  {4, -3, 5, -2, -1, 2, 6, -2} is %d \n", maxSum);    

    return 0;
}