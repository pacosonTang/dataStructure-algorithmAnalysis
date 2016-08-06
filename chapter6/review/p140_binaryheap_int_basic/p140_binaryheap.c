#include "binaryheap.h"

int main()
{
	int i;
	BinaryHeap bh;
	int capacity;
	int size;
	ElementType data[] =  {85, 80, 40, 30, 10, 70, 110};

	capacity = 15;
	size = 7;
	bh = initBinaryHeap(capacity);

	printf("\ninsert {85, 80, 40, 30, 10, 70, 110} into binary heap.");
	for(i = 0; i < size; i++)
	{
		insert(data[i], bh);
	}	
	printBinaryHeap(bh);

	printf("\ninsert {100, 20, 90, 5} into binary heap\n");
	insert(100, bh);
	insert(20, bh);
	insert(90, bh);
	insert(5, bh);
	printBinaryHeap(bh);

	printf("\ndeleteMin from binary heap\n");
    deleteMin(bh);  
    printBinaryHeap(bh);    
     
	// other operations in bianry heap      
    printf("\nincreaseKey(2, 85, bh) [increaseKey(index, increment, binary heap)]\n");
    increaseKey(2, 85, bh);
    printBinaryHeap(bh);
	
	printf("\ndecreaseKey(9, 85, bh) [decreaseKey(index, decrement, binary heap)]\n");
    decreaseKey(9, 85, bh);
    printBinaryHeap(bh);
	
	return 0;
}