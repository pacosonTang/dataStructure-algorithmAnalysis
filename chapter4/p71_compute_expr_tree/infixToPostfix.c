#include "stack.h"

#define Size 100

// refer to p50.c and put it into the same project
extern struct Stack;
typedef struct Stack *Stack;
Stack operand; // declaration of Stack operand 
int isOperator(char ch);
void infir_to_postfix();

//compare operator's priority between ch1 and ch2, return -1, 0 or 1 
int priorityBigger(char ch1, char ch2)
{
	int size = 8;
	char operator_[]={ '(', ')', ' ', '+', '-', ' ', '*', '/'};
	int index1, index2;
	int i;

	if(ch1 - ch2 == 0)
		return 0;

	for(i = 0; i< size; i++)
		if(operator_[i] == ch1)
		 	index1 = i;			 
		else if(operator_[i] == ch2)
		 	index2 = i;					 
	
	index1 -= index2;

	if(index1 == 1 || index1 == -1) 
		return 0;
	else if(index1 > 1)
		return 1;
	else if(index1 < -1)
		return -1;	
}


//judge whether the ch is operator or not ,also 1 or 0
int isOperator(char ch)
{
	int size;
	char operator_[]={'(', '+', '-', '*', '/', ')'};
	int i;

	size = 6;
	for(i = 0; i < size; i++)
		if(ch == operator_[i])
			break;

	return i == size ? 0 : 1;
}

//convert a part of str with length len into responding element value 
ElementType strToElement(int *str, int len)
{
	int i;
	int value;

	i = value = 0;
	while(i < len)
	{
		value += *(str+i) - 48;
		if(++i == len)
			break;
		value *= 10;
	}
	return value;
}

// convert infix expr into postfix expr
//for operand and operator cannot be in the same type ,we treat them as char and split them with space
void infixToPostfix(Stack s1, Stack s2,char *expr)
{
	char ch;	
	int i;
	char top_t;	
	int flag;		

	i = 0;	
	flag = 0;	 
	while((ch = *(expr+i++)) != '\0') 
	{				
		if(ch == ')'){// if ch equals ')', pop elements in stack s2 between '(' and ')' into stack s1
			while((top_t = top(s2)) != '(' ) 
			{			
				push(top_t, s1);
				push(' ', s1);
				pop(s2);
			}			
			pop(s2); // pop '(' in stack s2 			
			continue;
		}

		if(isOperator(ch)) // isOperator is true					
		{ 
			if(ch == '(') 
			{
				push(ch, s2); // push '(' into operator stack s2
				flag = 1;
				continue;
			}			

			while((top_t = top(s2)) != -1 && priorityBigger(top_t, ch) >= 0 && flag ==0) 
			{							
				pop(s2);				 
				push(top_t, s1);
				push(' ', s1);	
			}												 
			push(ch, s2); // push operator into operator stack s2 		 
			flag = 0;
		}
		else 
		{
			push(ch, s1);					 
			push(' ', s1);    // we treat them as char and split them with space
		}
			
	}
	// pop element in s2 and push it into s1
	while(!isEmpty(s2)) 
	{		
		push(top(s2), s1);
		push(' ', s1);
		pop(s2);
	}	
}

// read expr from console till '\n' and we just only focus on '+' and '*';
// postfix expression like 6 5 2 3 + 8 * + 3 + *
char *read()
{
	char *temp;
	int len;		
	char ch;
			
	temp = (char*)malloc(Size * sizeof(char));
	len = 0;			
	while((ch = getchar()) != '\n') 
	{	
		if(ch == ' ')
			continue;
		temp[len++] = ch;	 
	}
		
	temp[len] = '\0';
	
	return temp;
}  

// there are 2 stacks, that's operand and operator;
//works list
//1.read expr, 2.convert the expr from infix to postfix, 3.

/*
int main()
{	
	Stack operand;
	Stack operator_;

	operand = createStack(Size);
	operator_ = createStack(Size);
	
	// convert infix into postfix expr
	infixToPostfix(operand, operator_, read());	
	printStack_postfix(operand);
	
	// compute postfix expr
	

	return 0;
}
*/

void infir_to_postfix()
{	
	Stack operator_;

	//create stack operand and operator_
	operand = createStack(Size);
	operator_ = createStack(Size);
	
	// convert infix into postfix expr
	infixToPostfix(operand, operator_, read());	
	printStack_postfix(operand);	
}
