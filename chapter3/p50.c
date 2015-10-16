#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define EmptyStack -1
#define Error(str) printf("%s",str) 
#define FatalError(str) printf("%s",str) 
#define minStackSize 5

struct Stack;
typedef struct Stack *Stack;

int isFull(Stack s);
int isEmpty(Stack s);
Stack createStack(int);
void disposeStack(Stack s);
void makeEmpty(Stack s);
void push(ElementType e, Stack s);
ElementType top(Stack s);
void pop(Stack s);
ElementType top(Stack s);

void printStack(Stack s); 

struct Stack {
	int capacity;
	int topOfStack;
	ElementType *array;
} ;

//judge whether the stack is empty or not
int isFull(Stack s)
{
	return s->capacity - 1 == s->topOfStack ? 1 : 0;	
}

//judge whether the stack is empty or not
int isEmpty(Stack s)
{
	return s->topOfStack == -1;
}

//create stack with the head node 
Stack createStack(int size)
{
	Stack s;
	
	s = (Stack)malloc(sizeof(struct Stack));

	if(size < minStackSize) {
		Error("stack size is too small, and creating stack with defualt size 5");	
		size = minStackSize;
	}
	if(s == NULL) {
		FatalError("out of space when allocting memory for stack s");
		return NULL;
	}

	s->array = (ElementType *)malloc(size * sizeof(ElementType));	
	if(s->array == NULL) {
		FatalError("out of space when allocting memory for stack's array ");
		return NULL;
	}
	s->topOfStack = -1;
	s->capacity = size;	
	return s;
}

//dispose stack 
void disposeStack(Stack s)
{
	free(s->array);
	free(s);
}

//pop all elements in the stack
void makeEmpty(Stack s)
{
	if(s->topOfStack == -1)
		Error("must create the stack first");
	while(!isEmpty(s))
		pop(s);
}

//push the node with value e into the stack s 
//attend that first moving ptr ,then executing push operation
void push(ElementType e, Stack s)
{
	ElementType *temp = s->array;
	
	if(isFull(s))
		Error("the Stack is full, push failure! ");			
	else{
		s->topOfStack ++;
		s->array[s->topOfStack] = e;				
	}		
}

// pop the node or element on the top of stack 
//attend that first executing pop operation,then moving ptr
void pop(Stack s)
{
		
	if(isEmpty(s))
		Error("empty stack");
	else 
		s->topOfStack --;							 
}

// return the value of the top node in the stack
ElementType top(Stack s)
{
	if(!isEmpty(s))		
		return s->array[s->topOfStack];
	Error("/n the stack is empty");
	return -1;
}

//print value of element in the stack s
void printStack(Stack s)
{
    int i;

    if(isEmpty(s)){
		Error("empty stack");
		return ;
    }
	
	for(i=0; i<= s->topOfStack; i++) 
		printf("%4d", s->array[i]);
	    
    printf("\n");
}

 int main()
{	
	int i;
	Stack s;		

	s = createStack(6);
	
	printf("\n\n\t\t ====== test for building stack in array ====== \n");

	printf("\n test for judging whether the stack is empty or not ,also 1 or 0 \n");
	printf("%4d", isEmpty(s));

	
	printf("\n test for executing %4d push operations into the stack \n", s->capacity);
	for(i = 1; i <= s->capacity; i++)
		push(i, s);
	printStack(s);
	
	printf("\n test for judging whether the stack is empty or not ,also 1 or 0 \n");
	printf("%4d", isEmpty(s));

	printf("\n test for executing 2 pop opeartions in the stack \n");	
	pop(s);
	pop(s);
	printStack(s); 
	
	printf("\n test for acquiring the value of top node in the stack \n");	
	printf("%4d", top(s)); 
		
	printf("\n test for making the stack empty  \n");	
	makeEmpty(s);	
	printStack(s);
				
	printf("\n test for judging whether the stack is empty or not ,also 1 or 0 \n");
	printf("%4d", isEmpty(s));

	printf("\n");

	return 0;
}


