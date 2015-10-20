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
int getTopOfStack(Stack s);
ElementType *getArray(Stack s);

void printStack(Stack s); 
void printStack_postfix(Stack s);

struct Stack {
	int capacity;
	int topOfStack;
	ElementType *array;
} ;
