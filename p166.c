#include <stdio.h>
#define ElementType int

/* 打印数组数据 */
void printArray(int* a, int N)
{
    int i;	    
    for(i = 0; i < N; i++)
        printf("%4d", a[i]);
    printf("\n");
}

/* 插入排序代码 */
void InsertSort(ElementType A[], int N)
{
    int j, p;
    ElementType tmp;

    for(p = 1; p < N; p++) {
        tmp = A[p];
        for(j = p; j > 0 && A[j - 1] > tmp; j--)
            A[j] = A[j - 1];
        A[j] = tmp;
    }
}

main()
{    
    ElementType A[] = {34, 8, 64, 51, 32, 21};
    char p[256];
    char* str = p;
    
    str = "initial array A: ";
    printf("%40s",str);
    printArray(A, 6);
    printf("\n");
    
    str = "after insert sorting , array A: ";
    printf("%40s", str);
    InsertSort(A, 6);
    printArray(A, 6);
}
