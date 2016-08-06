#include "binaryheap_struct_pointer.h"

// 堆节点是结构体指针类型.
int main()
{	
	BinaryHeap bh;
	int i, capacity, size;	
	int data[] =  {85, 80, 40, 30, 10, 70, 110};

	capacity = 15;
	size = 7;
	bh = initBinaryHeap(capacity);

	printf("\ninsert {85, 80, 40, 30, 10, 70, 110} into binary heap.");
	for(i = 0; i < size; i++)
	{
		insert(createElementType(data[i]), bh);
	}	
	printBinaryHeap(bh);

	
	printf("\ninsert {100, 20, 90, 5} into binary heap\n");
	insert(createElementType(100), bh);
	insert(createElementType(20), bh);
	insert(createElementType(90), bh);
	insert(createElementType(5), bh);
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