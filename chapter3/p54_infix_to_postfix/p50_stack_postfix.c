#include <stdio.h>
#include <malloc.h>

#define ElementType char
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
void printStack_postfix(Stack s);

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
	Error("the stack is empty from func top\n");
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

//print value of element in the stack s with postfix
void printStack_postfix(Stack s)
{
    int i;

    if(isEmpty(s)){
		Error("empty stack");
		return ;
    }
	printf("stack elements list: ");
	for(i=0; i<= s->topOfStack; i++)  	
		printf("%c", s->array[i]);
	 	    
    printf("\n");
}