#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n\t error: %s \n",str) 

struct Node;
typedef struct Node *Node;

struct Node
{
	int value;
	Node next;
};

struct BucketSet;
typedef struct BucketSet* BucketSet;

struct BucketSet
{
	int size;
	Node* array;
};

BucketSet initBucketSet();
void printArray(ElementType* data, int size);
Node createNode(int value);
void bucketsort(Node* buckets, ElementType value, int bit);
int singleBit(int value, int bit);

// allocate for new Node with value.
Node createNode(int value)
{
	Node temp = (Node)malloc(sizeof(struct Node));
	if(temp==NULL)
	{
		Error("failed createBucket() for out of space.");
		return NULL;
	}
	temp->next = NULL;
	temp->value = value;
	return temp;
}

// allocate the memory for the bucket and bucket ptr
BucketSet initBucketSet(int size)
{
	BucketSet bucketSet;	
	int i;

	// allocate memory for BucketSet.
	bucketSet = (BucketSet)malloc(sizeof(struct BucketSet));
	if(bucketSet==NULL)
	{
		Error("failed initBucketSet() for out of space.");
		return NULL;	
	}
	bucketSet->size = size;
	
	// allocate memory for BucketSet->buckets.
	bucketSet->array = (Node*)malloc(size * sizeof(Node));
	if(!bucketSet->array)
	{
		Error("failed initBucketSet() for out of space.");
		return NULL;	
	}	
	
	// allocate memory for every unit in BucketSet->buckets.
	for(i=0; i<size; i++)
	{
		bucketSet->array[i] = createNode(-1);
		if(bucketSet->array[i]==NULL)
		{			
			Error("failed initBucketSet() for out of space.");
			return NULL;
		}		
	}
	return bucketSet;
}

// get the integer under the bit.
int singleBit(int value, int bit)
{
	int i=1;

	while(i++ < bit)
	{
		value /= 10;
	}
	return value%10;
}

// details of bucketsort for input data. 
void bucketsort(Node* buckets, ElementType value, int bit)
{			
	int index = singleBit(value, bit);
	Node temp = buckets[index]; // value is treated as direct or indirect index.
	
	while(temp->next)
	{
		temp = temp->next;
	}
	temp->next = createNode(value);	
}

// 桶的存储结构 copy 会 数组.
void bucketsToArray(BucketSet bucketSet, ElementType* array)
{
	Node* buckets = bucketSet->array;
	Node temp;
	int size = bucketSet->size;
	int i, j=0;

	for(i=0; i<size; i++)
	{
		temp = buckets[i];
		while(temp->next)
		{			
			array[j++] = temp->next->value;
			temp = temp->next;
		}
	}
}

// 打印数组.
void printArray(ElementType* data, int size)
{
	int i;

	for(i = 0; i < size; i++)	 
		printf("\n\t data[%d] = %d", i, data[i]);					 
	printf("\n");
} 