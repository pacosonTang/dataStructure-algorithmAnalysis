#include <stdio.h>

#define ElementType int
#define CUTOFF 3

/* 打印数组数据 */
void printArray(int* a, int N)
{
	int i;

    for(i = 0; i < N; i++)
        printf("%4d", a[i]);
    printf("\n");
}

/* 交换元素 *a 与 *b */
void swap(ElementType *a, ElementType *b)
{
    ElementType temp;
    temp = *a; 
    *a = *b; 
    *b = temp;
}

//  （三数中值分割法）求三数中值（中位数）center == 均值向下取整*/
ElementType Median3(ElementType A[], int left, int right)
{ 
    int center = (left + right) /2; 

    if(A[left] > A[center])
        swap(&A[left], &A[center]);
    if(A[left] > A[right])
        swap(&A[left], &A[right]); 
    if(A[center] > A[right])
        swap(&A[center], &A[right]);
    swap(&A[center], &A[right - 1]);    // 将中位数隐藏到倒数第2个元素 */
    return A[right - 1];
}

/* 插入排序 */
void InsertionSort(ElementType A[], int N)
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

/* 快速排序 */
void Qsort(ElementType A[], int left, int right)
{
    int i, j;
    ElementType pivot;    

    if(left + CUTOFF <= right) { /* rihgt-left>=3,才有三数中值分割法的应用 */
        pivot = Median3(A, left, right);    /* 三数分割Median3把最大元放入A[right]了，枢纽元放入A[right-1]，最小元放入A[left] */
        i = left;
        j = right - 1;
		for(;;) {
            while(A[++i] < pivot);    /* 找大元素，i停在那里,i起始从 left+1 */
			while(A[--j] > pivot);    /* 找小元素，j停在那里,j起始从 right-2 */
			if(i < j)
				swap(&A[i], &A[j]);    /* 分割结束 */
			else break;
        }
        swap(&A[i], &A[right-1]); /* A[i]最后指向大元素，A[right-1]指向枢纽元，将它们交换*/        
        Qsort(A, left, i-1);  		/* 借助于二叉树分析递归步骤 */
        Qsort(A, i+1, right);		/* 借助于二叉树分析递归步骤 */
    } 
    else	/* 当数组长度小于cutoff-隔断距离的话，那么就采用插入排序，因为这样效率高些, 插入排序代码稍后我们补充*/
		InsertionSort(A+left, right-left+1);
}

main()
{    
	ElementType A[] = {34, 8, 64, 51, 32, 21, 8, 64};
    char p[256];
    char* str = p;
	int num = 8;
	
    printf("\t\t\t ========== test for quick sorting ==========\n\n");
    str = "initial array A: ";
    printf("%40s",str);
    printArray(A, num);    
    
    str = "after quick sorting , array A: ";
    printf("%40s", str);
	
    Qsort(A, 0, num-1);
    printArray(A, num);
}
