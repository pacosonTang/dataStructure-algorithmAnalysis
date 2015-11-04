#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)

void printArray(ElementType data[], int size);

void mergeArray(ElementType *data, ElementType *temp, int left, int center, int right)
{
	int start1;
	int start2;
	int end1;
	int end2;
	int index;

	start1 = left;
	end1 = center;
	start2 = center + 1;
	end2 = right;
	index = left;

	while(start1 <= end1 && start2 <= end2)
		if(data[start1] < data[start2])
			temp[index++] = data[start1++];
		else
			temp[index++] = data[start2++];
	while(start1 <= end1)
		temp[index++] = data[start1++];
	while(start2 <= end2)
		temp[index++] = data[start2++];

	for(index = left; index <= right ; index++)
		data[index] = temp[index];
}

void mergeSort(ElementType *data, ElementType *temp, int left, int right)
{
	int center;
	if(left < right)
	{
		center = (left + right) / 2;
		mergeSort(data, temp, left, center);
		mergeSort(data, temp, center + 1, right);
		mergeArray(data, temp, left, center, right);
	}
} 

int main()
{ 
	int size;
	ElementType data[] = {10, 100, 20, 90, 60, 50, 120, 140, 130, 5};
	ElementType *temp;
	
	size = 10;
	
	printf("\n\t=== test for building heap with {10, 100, 20, 90, 60, 50, 120, 140, 130, 5} ===\n");		
	printf("\n\t=== before executing merge sorting ===\n");	
	printArray(data, size);	

	temp = malloc(size * sizeof(ElementType));
	if(!temp)
	{
		Error("out of space, from func main");        
        return -1;
	}

	mergeSort(data, temp, 0, size-1);	
	// void mergeSort(ElementType *data, ElementType *temp, int left, int right)
	printf("\n\t=== after executing merge sorting ===\n");		
	printArray(data, size);	

	return 0;
}

void printArray(ElementType data[], int size)
{
	int i;

	for(i = 0; i < size; i++)	 
		printf("\n\t index[%d] = %d", i, data[i]);					 
	printf("\n");
} 
