#include <stdio.h>
#include <math.h>
// 对增量序列赋值 和 找出所需要的最大轮数.
// 如 Rebort Sedgewick(罗伯特·塞奇威克) 提出的 increment = 9*4^i - 9*2^i +1  或 increment = 4^i - 3*2^i +1;
// incrementSeq[] 起点从1 开始.
int incrementSeqFunc(int* incrementSeq, int length)
{	
	int i, startup1 =0 , startup2 = 2;

	for(i=0; i<length; i++)
	{
		if(i%2==0)
		{
			incrementSeq[i] = 9*pow(4, startup1) - 9*pow(2, startup1) +1;
			startup1++;
		}
		else
		{
			incrementSeq[i] = pow(4, startup2) - 3*pow(2, startup2) +1;
			startup2++;
		}
		if(incrementSeq[i] >= length)
		{
			break;
		}
	}
	return i; // 排序轮数，每轮都使用（比上一轮）缩小的增量序列
}

void printArray(int data[], int size)
{
	int i;
 
	for(i = 0; i < size; i++)
		printf("%d ", data[i]);
	
	printf("\n");
}

void shell_sort(int* array, int length)
{	
	int incrementSeq[255]; // 增量序列(startup == 0).
	int i, j, round=incrementSeqFunc(incrementSeq, length);
	int increment, temp;

	for(; round>=1; round--)
	{
		increment = incrementSeq[round-1];
		for(i=1*increment; i<length; i+=increment) // 默认地,array[0*increment]有序，所以从1*increment开始.
		{
			temp = array[i]; // 第1个无序成员.
			for(j=i-increment; j>=0; j-=increment) // j 在有序部分进行滑动.
			{
				if(temp < array[j])
				{
					array[j+increment] = array[j];
				}
				else
				{
					break;
				}
			}
			array[j+increment] = temp;
		}
	}	
}