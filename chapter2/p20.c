#include<stdio.h>

#define ElementType int

int max3(int i, int j, int k)
{
    if(i < j)
        i = j;
    if(i < k)
        i = k;
    return i;
}

int maxSubsequenceSum(int A[], int left, int right)
{
/* maxLeftSum左半部分最大和，maxLeftBorderSum左半边界（带左半最右边元素如A[3]）最大和，leftBorderSum左半边界和 */
    int maxLeftSum, maxRightSum;
    int maxLeftBorderSum, maxRightBorderSum;
    int leftBorderSum ,rightBorderSum;
    int center, i;
    
    if(left == right)
        if(A[left] > 0)
            return A[left];
        else
	    return 0;

    center = (left + right) / 2; /* 向下取整 */
    maxLeftSum = maxSubsequenceSum(A, left, center);    /* 左半最大子序列和 */
    maxRightSum = maxSubsequenceSum(A, center + 1, right);

    maxLeftBorderSum = 0;    /* 左半边界最大和 */
    leftBorderSum = 0;    /* 左半边界和 */
    for(i = center; i >= left; i--) 
    {    /* 这里貌似用了方法二种的遍历方式，起点是center， end是左半首元素 */
        leftBorderSum += A[i];
        if(leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }
    
	/* 同理 */
    maxRightBorderSum = 0;
    rightBorderSum = 0;
    for(i = center + 1; i <= right; i++) 
    {  /* 这里貌似用了方法二种的遍历方式，起点是center + 1， end是右半末元素 */
        rightBorderSum += A[i];
        if(rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }
	/* 求左半最大，右半最大，（左半边界最大+右半边界最大）的最大者 */
    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);  
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

    printf("\t ========== [third method-devide and conquer] test for maximum sum of subsequence ==========\n\n");
    str = "initial array A: ";
    printf("%50s",str);
    printArray(A, N);    

    str = "after computing maximum sum of subsequence: ";
    printf("%50s", str);
    maxSum = maxSubsequenceSum(A, 0, N-1);
    printArray(A, N);

    str = "maximum sum of array subsequence is: ";
    printf("%50s", str);
    printf("%4d\n\n", maxSum);

    return 0;
}
