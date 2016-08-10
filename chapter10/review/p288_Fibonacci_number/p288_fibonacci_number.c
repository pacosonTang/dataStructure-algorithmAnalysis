#include <stdio.h>

int elements[255];

// 计算斐波那契数的线性算法
void fibonacci(int index)
{
	if(index==0)
	{
		elements[index]=0;
	}
	else if(index==1)
	{
		elements[index]=1;
	}
	else // 还必须要这个 else 语句.
	{
		elements[index] = elements[index-1] + elements[index-2];
	}	
}

void main()
{
	int i;
	int size = 10;	

	for(i=0; i<size; i++)
	{
		fibonacci(i);
		printf("fibonacci(%d) = %d\n", i, elements[i]);
	}
}