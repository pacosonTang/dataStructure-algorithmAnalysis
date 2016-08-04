#include "queue.h"

void main()
{
	ElementType array[] = {3, 4, 6, 1, 2, 0, 10, 8, 9};
	Queue queue;
	int capacity=6;
	int i;
	
	queue=initQueue(capacity); // 初始化队列
	if(queue == NULL)
	{
		return ;
	}
	
	printf("\nlet {3, 4, 6, 1, 2, 0, 10, 8, 9} enter queue.\n");
	for(i=0; i<9; i++)
	{
		enQueue(queue, array[i]); // 让元素进队列
	}
	printf("\n\nthe elements in queue are as follows: ");
	printQueue(queue);
	
	// 让元素出队列
	deQueue(queue);
	deQueue(queue);
	deQueue(queue);
	enQueue(queue, array[6]);
	enQueue(queue, array[7]);
	enQueue(queue, array[8]);
	printf("\n\nafter 3 dequeue operations and enQueue({10,8,9}) ,the elements in queue are as follows: ");
	printQueue(queue);

	printArray(queue);
}