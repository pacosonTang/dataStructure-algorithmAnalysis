#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s\n", str)

struct Queue;
typedef struct Queue* Queue;

struct Queue
{
	int capacity;
	int size;
	int front;
	int rear;
	ElementType* array;
};

Queue makeEmptyQueue(Queue queue, int);
Queue initQueue(int size);
void printQueue(Queue q);
int isFull(Queue queue);
int isEmpty(Queue queue);
void enQueue(Queue queue, ElementType element);
ElementType deQueue(Queue queue);
void disposeQueue(Queue q);