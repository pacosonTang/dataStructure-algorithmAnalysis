#include <stdio.h>

#define ElementType int

void swap(ElementType *, ElementType *);

/*  （三数中值分割法）求三数中值（中位数）center == 均值向下取整*/
ElementType Median3(ElementType A[], int left, int right)
{ 
    int center = (left + right) / 2; 

    if(A[left] > A[center])
        swap(&A[left], &A[center]);
    if(A[left] > A[right])
        swap(&A[left], &A[right]); 
    if(A[center] > A[right])
        swap(&A[center], &A[right]);
    swap(&A[center], &A[right - 1]);    /* 将中位数隐藏到倒数第2个元素 */
    return A[right - 1];
}
/* 交换元素 *a 与 *b */
void swap(ElementType *a, ElementType *b)
{
    ElementType temp;
    temp = *a; 
    *a = *b; 
    *b = temp;
}
void test_Median3() 
{
    ElementType A[] = {8, 1, 4, 9, 0, 3, 5, 2, 7, 6}; 
    int temp = Median3(A, 0, 9);
    printf("The median of {8, 1, 4, 9, 0, 3, 5, 2, 7, 6} is  %4d\n",temp);          
} 

int main()
{
	test_Median3();
	return 0;
}