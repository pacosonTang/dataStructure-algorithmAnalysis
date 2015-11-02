#include <stdio.h>
#include <math.h>


// 计算 log 以2为底的对数
double log2(double input)
{	
	return log(input) / log(2);	
}

// we adopt ascending order to execute shellSorting operation
void shellSort(int data[], int size)
{
	int temp;
	int round;
	int index;
	int i;
	int offset;

	round = (int)log2(size);	

	for(; round > 0;) 
	{
		offset = (int)pow(2, round) - 1; // assignment of offset, like 7, 3, 1 		
		for(i = offset; i < size; i++) // i like 7, 8, 9, ...., size-1 
		{					
			temp = data[i];// the idea refers to the insertion sort 			
			for(index = i; index >= offset; index -= offset)		 			
				if(temp < data[index - offset])				
					data[index] = data[index - offset];
				else
					break;			
			data[index] = temp;
		}
		round --;
	}
}

void printArray(int data[], int size)
{
	int i;
 
	for(i = 0; i < size; i++)
		printf("%5d", data[i]);
	
	printf("\n");
}

int main()
{ 
	int size;
	int data[] = {100, 1000, 100, 10, 6, 2, 19, 25, 15, 55, 35, 5, 110, 120, 119};
		
	size = 15;

	printf("\n=== before executing shellSort ===\n");
	printArray(data, size);
	shellSort(data, size);
	printf("\n=== after executing shellSort ===\n");
	printArray(data, size);	
	 
	 
 
	
	return 0;
}