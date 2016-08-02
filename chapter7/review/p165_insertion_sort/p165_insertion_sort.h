#include <stdio.h>

// 以升序进行插入排序.
void insertion_sort(int* array, int length)
{
	// i 表示有序数组的成员个数.
	int i, j;	
	int temp;

	// 第1个数字(下标==0)本就有序，所以 i从1开始计算.
	for(i=1; i<length; i++)
	{
		temp = array[i];
		for(j=i-1; j>=0 && temp<array[j]; j--) // j 在有序数组范围内滑动（右→左）.
		{			
			array[j+1] = array[j];// （从右到左）后移
		}
		array[j+1] = temp;		
	}
}

void printArray(int* data, int length)
{
	int i;

	for(i=0; i<length; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");
}