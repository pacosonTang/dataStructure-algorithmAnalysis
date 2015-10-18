#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define MinQueueSize 5
#define Error(str) printf("%s",str)   
#define FatalError(str) printf("%s",str) 
#define OK 1
#define ERROR 0

struct Node;
typedef struct Node *Node;
struct Queue;
typedef struct Queue *Queue;

int isEmpty(Queue);
int isFull(Queue);
Queue createQueue();
void disposeQueue(Queue q);
void makeEmpty(Queue q);
void enQueue(ElementType x, Queue q);
void front(ElementType* x,Queue q);
void deQueue(ElementType* x,Queue q);

struct Node
{
    ElementType value;
    Node next;
};

struct Queue
{	
	Node front;
	Node rear;	
};

//judge whether the queue is empty or not
int isEmpty(Queue q)
{
    return (q->front->next == NULL) && (q->rear->next == NULL);
}

//judge whether the queue is full or not
int isFull(Queue q)
{
    return q->rear->next == q->front;
}

//create queue with initializing array, capacity, front, rear, size; 
Queue createQueue()
{
    Queue q;	

    q = (Queue)malloc(sizeof(struct Queue));
    if(!q) {
        FatalError("out of space");        
        return NULL;
    }        	
	
    makeEmpty(q);
    return q;
} 

//building empty queue by initializing front and rear 
void makeEmpty(Queue q)
{	
	Node n;

	n = (Node)malloc(sizeof(struct Node));
    if(!n) {
        FatalError("out of space, from func makeEmpty ! ");        
        return ;
    }

	n->next = NULL;
	q->front = n;
	q->rear = n;    
}

//element enter the queue
void enQueue(ElementType x, Queue q)
{
	Node n;

    if(isFull(q)) { // if the queue is full, the element cannot enter the queue
		FatalError(" for the queue is full, the element cannot enter the queue; from func enQueue ");        
		return ;
	}

	n = (Node)malloc(sizeof(struct Node));	
	if(!n) { 
		FatalError("\n out of space, from func enQueue \n");
		return ;
	}	
	n->value = x;
	n->next = NULL;		

	if(q->front->next == NULL) // initializing the front of queue
		q->front->next = n;		
	q->rear->next = n; 				
	q->rear = n;	
	q->rear->next = q->front->next; // let the queue be a cycle queue
}

//element departs the queue
void deQueue(ElementType* e, Queue q)
{
	Node temp;

    if(isEmpty(q))  // if the queue is empty, there's no element departing the queue
	{
		Error("\n for the queue is empty, there's no element departing the queue; from func deQueue \n");
		e = NULL;
		return ;
	}
	
	temp = q->front->next;	//temp proves to not equal to NULL;
	*e = temp->value;		
	q->front->next = temp->next;
	if(temp == temp->next){ // the queue has only a node departing from the queue now
		q->front->next = NULL;
		q->rear = q->front;
	}
	else
		q->rear->next = q->front->next; // let the queue be a cycle queue	
	free(temp);	
}

void front(ElementType* e,Queue q)
{
	 if(isEmpty(q))  // if the queue is empty, there's no element for returning
	{
		Error("\n for the queue is empty, there's no element for returning; from func front \n");
		e = NULL;
		return ;
	}        
    *e = q->front->next->value;    
}

//dispose the queue by free its relative memory
void disposeQueue(Queue q)
{
    if(q) 
	{	
		if(q->front)
			free(q->front);
		if(q->rear)
			free(q->rear);
		free(q);
    }    
}

//print queue's element value
void printQueue(Queue q)
{        
	Node temp;
    	
	if(isEmpty(q))
	{
		printf("\n the queue is empty, from func printQueue \n");
		return ;
	}
	
	temp = q->front->next;
    printf("\n\n the queue's array elements: ");
    while(temp && temp != q->rear) {
        printf("%2d", temp->value);
		temp = temp->next;
	}
	printf("%2d", temp->value);
    printf("\n");
}

int main()
{
    int i;
	Queue q;		
	int temp;
	int capacity = 6;

	q = createQueue();
	
	printf("\n\n\t\t ====== test for building Queue in link ====== \n");
	printf("\n test for judging whether the Queue is empty or not ,also 1 or 0 : ");
	printf("%4d \n", isEmpty(q));	
	
	printf("\n test for executing %4d enQueue operations into the Queue \n", capacity);
	for(i = 1; i <= capacity; i++)
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
	if(&temp)
		printf("%2d\n", temp); 
	
	/* test for dequeue operations to let the queue empty */	
	printf("\n test for executing 5 deQueue opeartions in the Queue \n");	
	for(i=0; i<5; i++) {
		deQueue(&temp,q);	
		printf("\n the value of element departing from the queue is %2d \n", temp);	
	}

	
	printf("\n test for making the Queue empty  \n");	
	makeEmpty(q);	
	printQueue(q); 
				
	printf("\n test for judging whether the Queue is empty or not ,also 1 or 0 : ");
	printf("%4d \n ", isEmpty(q));

	printf("\n");
	
    return 0;
}

