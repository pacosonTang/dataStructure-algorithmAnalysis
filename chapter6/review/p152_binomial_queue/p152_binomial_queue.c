#include "p152_binomial_queue.h"

int main()
{
	BinomialQueue bq1, bq2;
	int data1[] =  {7, 6, 1, 2, 4, 3, 5};
	int data2[] = {65, 24, 12, 51, 16, 18};	
	int data3[] = {24, 65, 51, 23, 14, 26, 13};
	int i;
	int capacity1, capacity2;
	int length1=7, length2=6;

	// creating the binominal queue bq1.
	capacity1 = 7;
	bq1 = init(capacity1);		
	for(i=0; i<length1; i++)
	{
		insert(bq1, data1[i]);
	}
	printf("\ninsert {7, 6, 1, 2, 4, 3, 5} into the  binominal queue1\n");	
	printBinomialQueue(bq1);	
	// creating over.

	// creating the binominal queue bq2.
	capacity2 = 3;
	bq2 = init(capacity2);		
	for(i=0; i<length2; i++)
	{
		insert(bq2, data2[i]);
	}
	printf("\ninsert {65, 24, 12, 51, 16, 18} into the  binominal queue2\n");	
	printBinomialQueue(bq2);	
	// creating over.

	// merge bq2 into the bq1 also bq1 as the final result.
	for(i=0; i<capacity2; i++)
	{
		if(bq2->array[i]!=NULL)
		{
			merge(bq1, bq2->array[i], i);
		}
	}
 	printf("\n=== merge bq1 and bq2 ===\n");
	printBinomialQueue(bq1);
	// merge over. 

	//deleteMin bq1.
	// find the pos with minimal.
	deleteMin(bq1);
	printf("\n=== deleteMin from bq1 \n");
	printBinomialQueue(bq1);
}