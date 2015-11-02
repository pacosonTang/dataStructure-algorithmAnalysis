#include <stdio.h>

// we adopt ascending order to execute inserting operation
void insert(int data[], int size)
{
	int temp;
	int p;
	int index;

	for(p = 1; p < size; p++)
	{
		temp = data[p];
		for(index = p - 1; index >= 0 && temp < data[index]; index--)				
			data[index+1] = data[index];
		data[index+1] = temp;
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
	int data[] = {100, 1000, 100, 10, 6, 2, 19, 25, 15};

	size = 8;

	printf("\n=== before executing inserting ===\n");
	printArray(data, size);
	insert(data, size);
	printf("\n=== after executing inserting ===\n");
	printArray(data, size);

	return 0;
}
