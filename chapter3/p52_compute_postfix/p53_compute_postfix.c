#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define Size 100
#define ElementType int

// refer to p50.c and put it into the same project
extern struct Stack;
typedef struct Stack *Stack;

extern Stack createStack(int);
extern void push(ElementType e, Stack s);
extern void pop(Stack s);
extern ElementType top(Stack s);
extern void printStack_postfix(Stack s); 
extern void infir_to_postfix();
extern int isOperator(char ch);
extern int getTopOfStack(Stack s);
extern ElementType *getArray(Stack s);

extern Stack operand;

int computeResult(int operand1, int operand2, int operator_)
{
	switch(operator_)
	{
	case '+': return operand1 + operand2;
	case '*': return operand1 * operand2;
	default: return 0; break;
	}
}

// compute final result of responding postfix 
ElementType compute_postfix()
{
	Stack output;
	int i;
	ElementType *p;
	int value;
	int operand1;
	int operand2;
	 
	output = createStack(Size);
	i = 0;
	p = getArray(operand);

	while(i < getTopOfStack(operand))
	{
		value = *(p+i++);
		if(value == ' ')
			continue;
		if(isOperator(value))
		{
			operand1 = top(output);
			pop(output);

			operand2 = top(output);
			pop(output);

			value = computeResult(operand1, operand2, value);
			push(value, output);
			continue;
		}
		push(value - 48, output);
	}
	return getArray(output)[0];
}

// there are 2 stacks, that's operand and operator;
//works list 1.read expr, 2.convert the expr from infix to postfix, 3.
int main()
{					
	// convert infix into postfix expr
	printf("\n ====== convert infix into postfix expr ====== \n");
	infir_to_postfix();	
	
	//compute postfix expr
	printf("\n ====== compute postfix expr ====== \n");
	printf("final result  = %4d \n", compute_postfix());
	return 0;
}