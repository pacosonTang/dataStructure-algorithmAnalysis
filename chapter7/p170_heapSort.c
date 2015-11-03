#include <stdio.h>
#define ElementType int

void swap(ElementType *x, ElementType *y)
{
	ElementType temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

// get the left child of node under index with startup zero
int leftChildFromZero(int index)
{
	return index * 2 + 1;
}

 // percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 0
 void percolateDownFromZero(int index, ElementType data[], int size)
 {		
	ElementType temp;
	int child;		

	for(temp = data[index]; leftChildFromZero(index) < size; index = child)
	{
		child = leftChildFromZero(index);
		if(child < size - 1 && data[child] > data[child+1])
			child++;
		if(temp > data[child])
			data[index] = data[child];
		else
			break;
	}
	data[index] = temp;
 }

// we adopt ascending order to execute shellSorting operation
void heapSort(ElementType data[], int size)
{		
	int i;

	for(i = size / 2; i >= 0; i--) // building the heap by percolating down
		percolateDownFromZero(i, data, size);			 
	for(i = size - 1; i > 0; i--) // delete the minimum element
	{
		swap(&data[0], &data[i]); // switch the minimal also the element with index 0 with the final element in the minimum heap
		percolateDownFromZero(0, data, i);
	}
} 

void printBinaryHeapFromZero(ElementType data[], int size)
{
	int i;

	for(i = 0; i < size; i++)
	{
		printf("\n\t index[%d] = ", i);
		if(i < size)
			printf("%d", data[i]);
		else
			printf("NULL");
	}
	printf("\n");
} 

int main()
{ 
	int size;
	int data[] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
	
	printf("\n\t=== test for building heap with {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130} ===\n");	
	size = 15;

	printf("\n\t=== before executing heap sorting ===\n");	
	printBinaryHeapFromZero(data, size);	
	heapSort(data, size);	
	printf("\n\t=== after executing heap sorting ===\n");		
	printBinaryHeapFromZero(data, size);

	return 0;
}