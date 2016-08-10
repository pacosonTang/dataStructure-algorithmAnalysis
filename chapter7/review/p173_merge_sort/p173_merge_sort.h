#include <stdio.h>
#include <malloc.h>

#define Error(str) printf("\nerror: %s", str)
#define ElementType int

ElementType* createArray(int size);
void mergeArray(ElementType* raw ,ElementType* temp, int left, int right);
void mergesort(ElementType* raw, ElementType* temp, int left, int right);
void printArray(ElementType data[], int size);

// allocate memory for array with size.
ElementType* createArray(int size)
{
	ElementType* array = (ElementType*)malloc(sizeof(ElementType)*size);
	
	if(array==NULL)
	{
		Error("failed createArray() for out of space.");		
	}
	return array;
}

// 合并数组raw[left,center] 和 数组raw[center+1, right] 到 temp数组.
void mergeArray(ElementType* raw ,ElementType* temp, int left, int right)
{
	int center = (left+right)/2;
	int start1, start2;	
	int end1, end2;	
	int index;

	start1 = left; //第一个数组起点.
	end1 = center; //第一个数组终点.
	start2 = center+1; // 第二个数组起点.
	end2 = right; // 第二个数组终点.
	index = left; // 数组索引.
	
	// 依序合并2个数组到 第3个数组 分3个steps：

	// step1: 把数组raw[left,center]或raw[center+1,right]中的元素copy到 temp数组中.
	while(start1 <= end1 && start2 <= end2)
	{
		if(raw[start1] < raw[start2]) // 谁小，谁就copy到 temp数组中.
		{
			temp[index++] = raw[start1++];
		}
		else
		{
			temp[index++] = raw[start2++];
		}
	} // step1 over.

	// 合并完后，肯定还有一个数组中的元素没有 copy完，因为两个数组的长度不等.
	// step2: 把没有copy完的数组中的元素copy到 temp数组中；
	while(start1 <= end1)
	{
		temp[index++] = raw[start1++];
	}	
	while(start2 <= end2)
	{
		temp[index++] = raw[start2++];
	} // step2 over.

	// step3: 现在temp 数组中的元素已经有序了，再把temp中的数组copy 回 raw数组中.
	for(index = left; index <= right ; index++)
	{
		raw[index] = temp[index];
	}
}

// 对数组raw[left, right]进行归并排序. 
// 归并排序是合并两个已排序的表，并吧合并结果存储到 第三个数组temp中.
void mergesort(ElementType* raw, ElementType* temp, int left, int right)
{
	int center;
	if(left < right)
	{
		center = (left + right) / 2;
		mergesort(raw, temp, left, center);
		mergesort(raw, temp, center + 1, right);
		mergeArray(raw, temp, left, right); // 合并已排序的两个表[left,center] 和 [center+1,right]
	}
}

void printArray(ElementType data[], int size)
{
	int i;

	for(i = 0; i < size; i++)	 
		printf("\n\t index[%d] = %d", i, data[i]);					 
	printf("\n");
} 