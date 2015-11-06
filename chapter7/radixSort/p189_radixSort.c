#include "p189_bucketSort.h"

#define Round 3

ElementType singleBit(ElementType value, int bit)
{
	int i;

	i = 1;
	while(i++ < bit)
		value = value / 10;		 
	return value % 10;
} 

//free the memory the buckets own
void clearBuckets(Node* buckets)
{
	int i;
	Node temp;	
	Node tempTwo;

	for(i = 0; i < MAX; i++)
	{
		temp = buckets[i]->next;
		buckets[i]->next = NULL;
		while(temp)
		{
			tempTwo = temp->next;
			free(temp);	
			temp = NULL;
			temp = tempTwo;
		}
	}
}

// proceeding the radix sorting for the array
void radixSort(Node* buckets, ElementType* data, int size)
{
	int i;
	int j;		

	for(i = 1; i <= Round; i++)
	{
		for(j=0; j<size; j++)		
			bucketSort(buckets, data[j], singleBit(data[j],i));
		// coducting bucket sorting for data array over
		
		bucketsToData(buckets, data);// and now, we update the data array from buckets		
		clearBuckets(buckets);
	}
}

int main()
{ 	
	int size;
	Node* buckets;
	ElementType data[] = {110, 245, 895, 658, 321, 852, 147, 458, 469, 159, 347, 28};

	printf("\n\t====== test for radix sorting towards the data array ======\n");
	printf("\n\t=== the initial array is as follows ===\n");
	size = 12;
	printArray(data, size);

	buckets = initBuckets();
	printf("\n\t=== the buckets array is as follows ===\n");
	radixSort(buckets, data, size);
	printArray(data, size); 

	//printf("%2d", singleBit(28, 4));

	return 0;
}
