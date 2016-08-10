#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\nerror: %s", str)

void swap(ElementType* a, ElementType* b);
ElementType median3(ElementType* array, int left, int right);
void quickselect(ElementType* array, int left, int right, int k);
void printArray(ElementType* array, int N);
void insertionSort(ElementType* array, int left, int right);

// swap array arraynd b.
void swap(ElementType* array, ElementType* b)
{
	ElementType t;

	t=*array;
	*array=*b;
	*b=t;
}

// 3数中值分割法 选出 left center right 分别存储最小，中间，最大值
// 然后 将中位数隐藏到倒数第2个元素 
ElementType median3(ElementType* array, int left, int right)
{	
	int center = (left+right)/2;

	if(array[left]>array[center])
	{
		swap(&array[left], &array[center]);	
	}
	if(array[left]>array[right])
	{
		swap(&array[left], &array[right]);	
	}
	if(array[center]>array[right])
	{
		swap(&array[center], &array[right]);	
	}
	/* 将中位数隐藏到倒数第2个元素 */
	swap(&array[center], &array[right-1]);
	return array[right-1];
}

/* 快速选择(第k+1个最大元素), 所以如果要选择第k个最大元素，main函数需要传入k-1 */
void quickselect(ElementType array[], int left, int right, int k)
{
    int i, j;
    ElementType pivot; // 枢轴.
	
	if(k>right)
	{
		Error("failed quickselect() for k is greater than right.");
		return;
	}

	// if(right-left >= 10) { also you can let lower limit be 10.
    if(right-left >= 3) { /* rihgt-left>=3,才有三数中值分割法的应用 */
		/* 三数分割 median3 把最大元放入array[right]了，枢纽元放入array[right-1]，最小元放入array[left] */
        pivot = median3(array, left, right);    
        i = left; //i 指向最小元.
        j = right-1; // j 指向枢纽元.
		for(;;) 
		{
            while(array[++i] < pivot);    /* (这里必须++i, 不能i++)找大元素，i停在那里,i起始从 left+1 */
			while(array[--j] > pivot);    /* (这里必须--j, 不能j--)找小元素，j停在那里,j起始从 right-2 */
			if(i<j)
			{
				swap(&array[i], &array[j]);    /* 分割结束 */
			}
			else
			{
				break;
			}
        }
		//key: array[i]最后指向大元素，array[right-1]指向枢纽元，将它们交换；		
        swap(&array[i], &array[right-1]);  
		// 交换后, array[i]=枢纽元, 前面的元素小于它, 后面的元素大于它.
		
		// 上面的代码和快速排序一样，下面的代码用于基于递归的快速选择
		if(k > i) 
		{
			quickselect(array, i+1, right, k);	
		}
		else if(k < i)
		{
			quickselect(array, left, i-1, k);	
		}
		// else k == i, bingo.		                
    } 
    else	/* 当数组长度小于3(10)的话，那么就采用插入排序，因为这样效率高些*/
	{
		insertionSort(array, left, right);
	}
}

// 插入排序
void insertionSort(ElementType* array, int left, int right)
{
	int i, j;
	ElementType temp;	

	for(i=left+1; i<=right; i++) // 下标i 存储无序部分的第一个元素，即下标i-1 存储有序的最后一个元素.
	{
		temp = array[i];
		for(j=i-1; j>=left; j--) // 下标j 初始存储有序部分的最后一个元素，并在有序部分逆向滑动.
		{
			if(temp < array[j])
			{
				array[j+1] = array[j];
			}
			else
			{
				break;
			}
		}
		array[j+1] = temp; // who not array[j]? 因为j--执行后 才推出了循环，所以要加回去.
	}
}

/* 打印数组数据 */
void printArray(int* array, int size)
{
	int i;

    for(i=0; i<size; i++)
	{
        printf("%d ", array[i]);
	}
    printf("\n");
}