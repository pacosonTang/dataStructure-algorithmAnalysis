#include<stdio.h>

#define ElementType int
#define NOTFOUND -1

/* A[]升序排列 */
int binarySearch(ElementType A[], ElementType x, int N)
{
    int low, mid, high;

    low = 0;
    high = N - 1;

    while (low <= high)
	{
        mid = (low + high) / 2;
        if(A[mid] < x)
            low = mid + 1;
        else if(A[mid] > x)
            high = mid - 1;
        else 
			return mid;
    }
    return NOTFOUND;
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
    int A[] = {4, 5, 67, 67, 109, 876};
    int N = 6;
    int x = 109;
    char p[256];
    char *str = p;
	
    printf("\t\t\t ========== test for binarySearch ==========\n\n");
    str = "initial array A: ";
    printf("%40s",str);
    printArray(A, N);    
	
    str = "the position whose value equals to: ";
    printf("%40s",str);     
    printf("%4d is %4d\n", x, binarySearch(A, x, N));
}




