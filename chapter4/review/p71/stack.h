#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define ERROR(str) printf(str)

struct Stack;
typedef struct Stack *Stack;

struct Stack
{
	int size;
	ElementType* head;
	int top;
};

int isFull(Stack s);
int isEmpty(Stack s);
Stack initStack(int size);
void push(Stack s, ElementType c);
void pop(Stack s, ElementType *e);
ElementType getTop(Stack s);
void reset(Stack s);

int isFull(Stack s)
{
	return s->size == s->top ? 1 : 0;
}

int isEmpty(Stack s)
{
	return 0 == s->top ? 1 : 0;
}

Stack initStack(int size)
{
	Stack s = (Stack)malloc(sizeof(struct Stack));
	if(s==NULL)
	{
		ERROR("error: failed initStack() for there is no spare space.\n");
	}
	else {
		s->size = size;
		s->top = 0;
		s->head = (ElementType*)malloc(sizeof(ElementType) * size);
		if(s->head==NULL)
		{
			ERROR("error: failed initStack() for there is no spare space.\n");
			return NULL;
		}
	}
	return s;
}

void push(Stack s, ElementType c)
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

void pop(Stack s, ElementType *e)
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

ElementType getTop(Stack s)
{
	ElementType value = 0;

	if(!isEmpty(s))
	{
		return s->head[s->top-1];
	}
	return -1;
}

void reset(Stack s)
{
	s->top = 0;
}