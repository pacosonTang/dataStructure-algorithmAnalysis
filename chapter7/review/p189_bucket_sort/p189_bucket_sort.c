#include "p189_bucket_sort.h"

void main()
{ 	
	BucketSet bucketSet;
	ElementType data[] = {9, 6, 3, 2, 7, 7, 1, 4, 1, 0, 3, 9, 1, 1};	
	int	size = 14, capacity=10;
	int i;

	bucketSet = initBucketSet(capacity);
	if(bucketSet==NULL)
	{
		return ;
	}  
	
	printf("\nbucketsort based on {9, 6, 3, 2, 7, 7, 1, 4, 1, 0, 3, 9, 1, 1}\n");	
	// 对10以内的数字进行桶排序.
	for(i=0; i<size; i++)
	{
		bucketsort(bucketSet->array, data[i]);	
	}	

	bucketsToArray(bucketSet, data);
	printArray(data, size);	
} 

