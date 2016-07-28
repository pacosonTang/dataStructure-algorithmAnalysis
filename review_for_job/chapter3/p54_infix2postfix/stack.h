#include <stdio.h>
#include <malloc.h>

typedef char ElementType;

typedef struct Stack
{
	int size;
	char* head;
	int top;
}Stack;

int isFull(Stack *s);
int isEmpty(Stack *s);
void initStack(Stack *s, int size);
void push(Stack *s, ElementType c);
void pop(Stack *s, ElementType *e);
ElementType getTop(Stack *s);

int isFull(Stack *s)
{
	return s->size == s->top ? 1 : 0;
}

int isEmpty(Stack *s)
{
	return 0 == s->top ? 1 : 0;
}

void initStack(Stack *s, int size)
{
	s->size = size;
	s->top = 0;
	s->head = (ElementType*)malloc(sizeof(ElementType) * size);
}

void push(Stack *s, ElementType c)
{
	if(!isFull(s))
	{
		s->head[s->top++] = c;
	} 
	else
	{
		printf("%s", "failed pushing for stack is full.");
	}
}

void pop(Stack *s, ElementType *e)
{
	if(!isEmpty(s))
	{
		*e = s->head[--s->top];
	}
	else
	{
		*e = ' ';
		printf("%s", "failed poping for stack is empty.");
	}	
}

ElementType getTop(Stack *s)
{
	if(!isEmpty(s))
	{
		return s->head[s->top-1];
	}
	printf("%s", "failed getTop for the stack is empty.");
	return -1;
}