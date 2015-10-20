#include "stack.h"

#define Size 100

// refer to p50.c and put it into the same project
extern struct Stack;
typedef struct Stack *Stack;

extern Stack operand; // operand is an extern variable defined in infixToPostfix 
extern int isOperator(char ch);
extern void infir_to_postfix();
int computeResult(int operand1, int operand2, int operator_);

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
	 
	output = createStack(Size); // create stack with length Size
	i = 0;
	p = getArray(operand); // get operand->array

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

