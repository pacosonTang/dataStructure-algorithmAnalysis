#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\nerror: %s", str)

struct Queue;
typedef struct Queue* Queue;

// 循环队列的数据结构.
struct Queue
{
	int capacity;
	int front;
	int rear;
	int size;
	ElementType* array;
};

Queue initQueue(int capacity);
int isFull(Queue queue);
void enQueue(Queue queue, ElementType e);
int isEmpty(Queue queue);
ElementType deQueue(Queue queue);
void printQueue(Queue queue);

// init queue wit capacity.
Queue initQueue(int capacity)
{
	// allocate memory for queue.
	Queue queue = (Queue)malloc(sizeof(struct Queue));	
	if(queue==NULL)
	{
		Error("failed initQueue() for out of space.");
		return NULL;			
	}		
	queue->capacity = capacity;
	queue->front = 0;
	queue->rear = 0;
	queue->size = 0;
	
	// allocate memory for queue->array.
	queue->array = (ElementType*)malloc(capacity * sizeof(ElementType));
	if(queue->array == NULL)
	{
		Error("failed initQueue() for out of space.");
		return NULL;
	}	
	return queue;
}

// judge whether the queue is full or not.
int isFull(Queue queue)
{
	return queue->size == queue->capacity ? 1 : 0;
}

// 进队列，满时不进.
void enQueue(Queue queue, ElementType e)
{	
	if(isFull(queue))
	{
		Error("failed enQueue() for the queue is full.");
		return ;
	}	
	queue->array[queue->rear++ % queue->capacity] = e;
	queue->size++;
}

// judge whether the queue is empty or not.
int isEmpty(Queue queue)
{
	return queue->size == 0 ? 1 : 0;
}

// 出队列，空时不出.
ElementType deQueue(Queue queue)
{
	int temp;
	if(isEmpty(queue))
	{
		Error("failed deQueue() for the queue is empty.");
		return -1;
	}

	temp = queue->array[queue->front++ % queue->capacity];
	queue->size--;
	return temp;
}

// 打印队列
void printQueue(Queue queue)
{
	int i, index;
	ElementType* array = queue->array;
	
	printf("\n");
	for(i=0; i<queue->size; i++)
	{
		index = (queue->front + i) % queue->capacity;
		printf("%d ", array[index]);
	}
	printf("\n");
}
