#include "infix2postfix.h" 

void computeExpr(Stack s, ElementType *postfix, int length)
{
	int i = 0;
	char c;
	ElementType num1, num2, result;

	for(;i<length;i++)
	{
		c = postfix[i];
		if(isOperator(c) == -1)// c is an operand.
		{
			push(s, c-48);
		}
		else if(isOperator(c) != -1) // c is an operator.
		{
			pop(s, &num1);
			pop(s, &num2);			

			switch(c)
			{
				case '+': result = num1+num2;break;
				case '-': result = num1-num2;break;
				case '*': result = num1*num2;break;
				case '/': result = num1/num2;break;
			}
			push(s, result);
		}
	}
	pop(s, &result);	
	printf("final computing result is %d \n", result);
}

int main()
{
	Stack s;	
	ElementType output[255];
	int length;

	s = initStack(1000);
	if(s==NULL)
	{
		return -1;
	}
	length = infix2postfix(s, output); //switch infix into postfix.
	printChatArray(output, length);
	
	// compute postfix expr.
	free(s);
	s=initStack(1000);
	computeExpr(s, output, length);

	return 0;
}