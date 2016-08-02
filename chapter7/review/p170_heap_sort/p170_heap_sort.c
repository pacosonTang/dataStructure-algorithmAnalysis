#include "p170_heap_sort.h"

int main()
{
	BinaryHeap heap;
	ElementType input[] = {31, 41, 59, 26, 53, 58, 97};
	int i, length = 7, capacity = 255;
	heap = buildHeap(capacity);
	
	// insert input array into the binary heap.
	printf("\ninsert {31, 41, 59, 26, 53, 58, 97} into binary heap.\n");
	for(i=0; i<length; i++)
	{
		insert(heap, input[i]);
	}

	// print the array sorted by heap.
	printBinaryHeap(heap->array, heap->size);

	// execute multiple deleteeMin operations for heap sorting.		
	for(i=0; i<length; i++)
	{
		deleteMin(heap);
	}
	// print the array sorted by heap.
	printf("\n after heap sort also executing length deleteMin operations. \n");
	printBinaryHeap(heap->array, length);
}