#include "queue.h"

//judge whether the queue is full or not, also 1 or 0
int isFull(Queue q)
{			
	return ((q->rear + 1) % q->capacity == q->front % q->capacity) && (q->size != 0); 	
}

//judge whether the queue is empty or not, also 1 or 0
int isEmpty(Queue queue)
{
	return queue->size == 0;
}

//initialize the queue with size
Queue initQueue(int size)
{
	Queue queue;	

	queue = (Queue)malloc(sizeof(struct Queue));
	if(!queue)
	{
		Error("failed initiation, for out of space, from initQueue");
		return NULL;
	}

	queue->capacity = size;
	makeEmptyQueue(queue, size);		

	return queue;
}

// allocate memory for members of the given queue
Queue makeEmptyQueue(Queue queue, int size)
{
	queue->array = (ElementType*)malloc(size * sizeof(ElementType));
	if(!queue->array)
	{
		Error("failed initiation, for out of space, from makeEmptyQueue");
		return NULL;
	}

	queue->size = 0;
	queue->rear = 0;
	queue->front = 1;

	return queue;
}

void enQueue(Queue queue, ElementType element)
{		
	if(isFull(queue))
	{
		Error("failed enQueue , for the queue is full, from func enQueue");
		return ;
	}

	queue->rear = (queue->rear + 1 ) % queue->capacity; 
	queue->array[queue->rear] = element;         
	queue->size++;
}

ElementType deQueue(Queue queue)
{
	ElementType temp;
	
	if(isEmpty(queue))
	{
		Error("failed deQueue , for the queue is empty, from func deQueue");
		return -1;
	}	

	queue->front %= queue->capacity;
	temp = queue->array[queue->front++];
	queue->size--;

	return temp;
}

//dispose the queue by free its relative memory
void disposeQueue(Queue q)
{
    if(q) 
	{
        free(q->array);
        free(q);
    }    
}

/*
int main()
{
	Queue queue;
	int size;

	size = 7;
	queue = initQueue(size);
	
	printf("test");

	enQueue(queue, 1);
	enQueue(queue, 2);
	enQueue(queue, 5);
	enQueue(queue, 3);
	printQueue(queue);

	deQueue(queue);	
	deQueue(queue);
	printQueue(queue);

	deQueue(queue);		
	deQueue(queue);	
	printQueue(queue);

	return 0;
}
*/

//print queue's element value
void printQueue(Queue q)
{        

    int i;
	
	if(isEmpty(q))
	{
		printf("\n the queue is empty, from func printQueue \n");
		return ;
	}

    printf("\n\n the queue's array elements: ");
    for(i = 0; i < q->size; i++)
        printf("%2d", q->array[(q->front+i)%q->capacity]);
    printf("\n");
}