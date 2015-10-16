#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define EmptyStack -1
#define Error(str) printf(" %s\n",str) 
#define FatalError(str) printf(" %s\n",str) 

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int isEmpty(Stack s);
Stack createStack(void);
void disposeStack(Stack s);
void makeEmpty(Stack s);
void push(ElementType e, Stack s);
ElementType top(Stack s);
void pop(Stack s);
void printStack(Stack s);

struct Node
{
    ElementType element;
    PtrToNode next;    
};

//judge whether the stack is empty or not
int isEmpty(Stack s)
{
	return s->next == NULL;
}

//create stack with the head node 
Stack createStack(void)
{
	Stack s;

	s = (Stack)malloc(sizeof(struct Node));
	if(s == NULL)
		FatalError("out of space");
	s->next = NULL;	
	return s;
}

//dispose stack 
void disposeStack(Stack s)
{
	free(s);
	s = NULL;
}

//pop all elements in the stack
void makeEmpty(Stack s)
{
	if(s == NULL)
		Error("must create the stack first");
	while(!isEmpty(s))
		pop(s);
}
//push the node with value e into the stack s 
void push(ElementType e, Stack s)
{
	PtrToNode temp;

	temp = (PtrToNode)malloc(sizeof(struct Node));
	if(temp == NULL)
		FatalError("out of space");
	else{
		temp->element = e;
		temp->next = s->next;
		s->next = temp;
	}		
}
// pop the node or element on the top of stack 
void pop(Stack s)
{
	PtrToNode temp;
	
	if(isEmpty(s))
		Error("empty stack");
	else{
		temp = s->next;
		s->next = temp->next;
		free(temp);
	}
}

//print value of element in the stack s
void printStack(Stack s)
{
    Stack temp;

    if(isEmpty(s)){
	Error("empty stack");
	return ;
    }

    temp = s->next;
    while (temp) {
        printf("%4d",temp->element);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{	
	int i;
	Stack s;		

	s = createStack();

	printf("\ntest for judging whether the stack is empty or not ,also 1 or 0 \n");
	printf("%4d", isEmpty(s));

	printf("\n test for executing 5 push operations into the stack \n");
	for(i = 1; i <= 5; i++)
		push(i, s);
	printStack(s);
	
	printf("\ntest for judging whether the stack is empty or not ,also 1 or 0 \n");
	printf("%4d", isEmpty(s));

	printf("\n test for executing 2 pop opeartions in the stack \n");	
	pop(s);
	pop(s);
	printStack(s);
	
	printf("\n test for making the stack empty  \n");	
	makeEmpty(s);	
	printStack(s);
				
	printf("\ntest for judging whether the stack is empty or not ,also 1 or 0 \n");
	printf("%4d", isEmpty(s));
	printf("\n");

	return 0;
}




