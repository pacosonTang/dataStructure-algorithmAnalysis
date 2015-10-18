#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define MinQueueSize 5
#define Error(str) printf("%s",str)   
#define FatalError(str) printf("%s",str) 
#define OK 1
#define ERROR 0

struct QueueRecord;
typedef struct QueueRecord* Queue;

int isEmpty(Queue);
int isFull(Queue);
Queue createQueue(int maxElements);
void disposeQueue(Queue q);
void makeEmpty(Queue q);
void enQueue(ElementType x, Queue q);
void front(ElementType* x,Queue q);
void deQueue(ElementType* x,Queue q);

struct QueueRecord
{
    int capacity;
    int front;
    int rear;
	int size;
    ElementType* array;
};

//judge whether the queue is empty or not
int isEmpty(Queue q)
{
    return q->size == 0;
}

//judge whether the queue is full or not
int isFull(Queue q)
{
    return ((q->rear + 1) % q->capacity == q->front) && (q->size != 0);
}

//create queue with initializing array, capacity, front, rear, size; 
Queue createQueue(int maxElements)
{
    Queue q;

    if(maxElements < MinQueueSize) {
        printf("\n\t\tQueue size is too small, default value is %2d\n", MinQueueSize);
        maxElements = MinQueueSize;
    }

    q = (Queue)malloc(sizeof(struct QueueRecord));
    if(!q) {
        FatalError("out of space");        
        return NULL;
    }
    
    q->array = (ElementType*)malloc(maxElements * sizeof(ElementType));
    if(!q->array) {
        FatalError("out of space");
        return NULL;
    }
    q->capacity = maxElements;
    makeEmpty(q);
    return q;
} 

//building empty queue by initializing size, front and rear 
void makeEmpty(Queue q)
{
	q->size = 0;
	q->front = 1;
	q->rear = 0;    
}

//element enter the queue
void enQueue(ElementType x, Queue q)
{
    if(isFull(q)) { // if the queue is full, the element cannot enter the queue
		Error("\n for the queue is full, the element cannot enter the queue; from func enQueue \n");
		return ;
	}
	q->rear = (q->rear + 1 ) % q->capacity; 
	q->array[q->rear] = x;         
	q->size++;
}

//element departs the queue
void deQueue(ElementType* e, Queue q)
{
    if(isEmpty(q))  // if the queue is empty, there's no element departing the queue
	{
		Error("\n for the queue is empty, there's no element departing the queue; from func deQueue \n");
		return ;
	}    	
    *e = q->array[q->front];    	
	q->front = (q->front + 1 )% q->capacity;
	q->size--;
}

void front(ElementType* e,Queue q)
{
	 if(isEmpty(q))  // if the queue is empty, there's no element for returning
	{
		Error("\n for the queue is empty, there's no element for returning; from func front \n");
		e = NULL;
		return ;
	}        
    *e = q->array[q->front];    
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

int main()
{
    int i;
	Queue q;		
	int temp;

	q = createQueue(6);
	
	printf("\n\n\t\t ====== test for building Queue in array ====== \n");
	printf("\n test for judging whether the Queue is empty or not ,also 1 or 0 : ");
	printf("%4d \n", isEmpty(q));
	
	
	printf("\n test for executing %4d enQueue operations into the Queue \n", q->capacity);
	for(i = 1; i <= q->capacity; i++)
		enQueue(i, q);
	printQueue(q);
	
	printf("\n test for judging whether the Queue is empty or not ,also 1 or 0 : ");
	printf("%4d \n", isEmpty(q));

	printf("\n test for executing 2 deQueue opeartions in the Queue \n");	
	deQueue(&temp,q);
	printf("\n the value of element departing from the queue is %2d \n", temp);	
	deQueue(&temp,q);
	printf("\n the value of element departing from the queu is %2d \n", temp);	
	printQueue(q);  
	
	printf("\n test for acquiring the value of front element in the Queue : ");	
	front(&temp, q);
	printf("%2d\n", temp); 
		
	printf("\n test for making the Queue empty  \n");	
	makeEmpty(q);	
	printQueue(q);
				
	printf("\n test for judging whether the Queue is empty or not ,also 1 or 0 : ");
	printf("%4d \n ", isEmpty(q));

	printf("\n");
	
    return 0;
}

