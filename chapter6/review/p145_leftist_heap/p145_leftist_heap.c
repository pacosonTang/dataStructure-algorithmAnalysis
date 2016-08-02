#include "leftist_heap.h"

int main()
{
	LeftistHeap h1 = NULL;
	LeftistHeap h2 = NULL;	
	int data1[] =  {21, 10, 23, 14, 3, 26, 17, 8};	
	int data2[] = {18, 12, 33, 24, 6, 37, 7, 18};
	int i;

	// insert {21, 10, 23, 14, 3, 26, 17, 8} into the leftist heap1.
	h1 = insert(h1, data1[0]);
	for(i=1; i<8; i++)
	{
		h1 = insert(h1, data1[i]);
	}
	printf("\ninsert {21, 10, 23, 14, 3, 26, 17, 8} into the leftist heap1\n");
	printPreorder(1, h1);

	// insert {18, 12, 33, 24, 6, 37, 7, 18} into the leftist heap2.
	h2 = insert(h2, data2[0]);
	for(i=1; i<8; i++)
	{
		h2 = insert(h2, data2[i]);
	}
	printf("\ninsert {18, 12, 33, 24, 6, 37, 7, 18} into the leftist heap2\n");
	printPreorder(1, h2);

	// merge h1 and h2.
	h1 = merge(h1, h2);
	printf("\nmerge heap1 and heap2\n");
	printPreorder(1, h1);

	// delete minimal tree node.
	h1 = deleteMin(h1);	
	printf("\n delete minimal tree node\n");
	printPreorder(1, h2);
}