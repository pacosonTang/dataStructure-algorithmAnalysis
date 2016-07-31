#include<stdio.h>

#define ElementType int

int max3(int i, int j, int k)
{
    if(i < j)
	{
        i = j;
	}
    if(i < k)
	{
        i = k;
	}
    return i;
}

// compute the maximum sum of sebsequence.
// 3 in mxSubSum3 means 3 possibilities. 
int maxSubSum3(int A[], int left, int right)
{
	int onlyLeftSum, onlyRightSum; // just only left or right sum without center.
    int centerLeftSum, centerRightSum; // the 3rd is passing center.
    int tempSum;
    int center, i;
    
    if(left==right)
	{
        if(A[left] > 0)
		{
            return A[left];
		}
        else
		{
			return 0;
		}
	}
    center = (left+right)/2;  
    onlyLeftSum = maxSubSum3(A, left, center);
    onlyRightSum = maxSubSum3(A, center + 1, right);

    centerLeftSum = 0;    
    tempSum = 0;    
    for(i=center; i>=left; i--) 
	{   
        tempSum += A[i];
        if(tempSum > centerLeftSum)
		{
            centerLeftSum = tempSum;
		}
    }
    	
    centerRightSum = 0;
    tempSum = 0;
    for(i=center+1; i<=right; i++) 
	{ 
        tempSum += A[i];
        if(tempSum > centerRightSum)
		{
            centerRightSum = tempSum;
		}
    }
	printf("onlyLeftSum=%d, onlyRightSum=%d, centerLeftSum + centerRightSum=%d \n", onlyLeftSum, onlyRightSum, centerLeftSum + centerRightSum);
	return max3(onlyLeftSum, onlyRightSum, centerLeftSum + centerRightSum);  
} 

int main()
{
    int N = 8, maxSum = 0;            
    ElementType A[] = {4, -3, 5, -2, -1, 2, 6, -2};        
    
    maxSum = maxSubSum3(A, 0, N-1);        
    printf("the maximum sum of array {4, -3, 5, -2, -1, 2, 6, -2} is: %d \n", maxSum);    	    
}