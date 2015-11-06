#include "p189_bucketSort.h"

// allocate the memory for the bucket and bucket ptr
Node *initBuckets()
{
	Node* buckets;
	int i;

	buckets = (Node*)malloc(MAX * sizeof(Node));
	if(!buckets)
	{
		Error("out of space, from func bucketSort!");
		return NULL;	
	}	
	
	for(i=0; i<MAX; i++)	
		buckets[i] = makeEmpty();	 
	return buckets;
}

//allocate the memory for the node and make it empty with evaluation of next
Node makeEmpty()
{
	Node temp; 

	temp = (Node)malloc(sizeof(struct Node));
	if(!temp)
	{
		Error("out of space, from func makeEmpty!");
		return NULL;	
	}
	temp->next = NULL;	

	return temp;
}

void bucketsToData(Node* buckets, ElementType *data)
{
	int i;
	int j;
	Node temp;

	i = 0;
	j = 0;
	while(i< MAX) // and now, we update the data array from buckets
	{
		temp = buckets[i]->next;
		while(temp)
		{
			data[j++] = temp->value;
			temp = temp->next;
		}
		i++;
	}
	// updating over	

}

// details of bucketSort for the input array data with size
void bucketSort(Node* buckets, ElementType data, int index)
{			
	Node temp;
	
	temp = buckets[index];
	while(temp->next)
		temp = temp->next;
	temp->next = makeEmpty();
	temp->next->value = data;
}

/*
int main()
{ 
	int size;
	int i;
	Node* buckets;
	ElementType data[] = {9, 6, 3, 2, 7, 7, 1, 4, 1, 0, 3, 9, 1, 1};

	printf("\n\t=== the initial array is as follows ===\n");
	size = 14;
	printArray(data, size);
	
	buckets = initBuckets();
	for(i=0; i<size; i++)
		bucketSort(buckets, data[i], data[i]);
	
	bucketsToData(buckets, data);
	printf("\n\t=== the buckets array is as follows ===\n");
	printArray(data, size);

	return 0;
}
*/

void printBuckets(Node* buckets)
{
	int i;
	Node node;
	
	for(i = 0;i<MAX; i++)
	{	
		if(!buckets[i]->next)
			continue;
		for(node = buckets[i]->next; node != NULL; node = node->next)
			printf("\n\t buckets[%d] = %d", i, node->value);
	}
	 
	printf("\n");
}

void printArray(ElementType data[], int size)
{
	int i;

	for(i = 0; i < size; i++)	 
		printf("\n\t data[%d] = %d", i, data[i]);					 
	printf("\n\n");
} 