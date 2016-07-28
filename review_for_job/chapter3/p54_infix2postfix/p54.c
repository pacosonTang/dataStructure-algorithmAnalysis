#include "stack.h"
#include "p54.h"
#include "math.h"

// just print array.
void printChatArray(char* array, int size)
{
	int i=0;

	for(;i<size; i++)
	{
		putchar(array[i]);
	}
	printf("\n\n");
}

// check whether the char is operator or not.
// if true returns priority with array index ,otherwise return -1.
int isOperator(char c)
{ 
	int i = 0;
	char priorities[] = {'(', ' ', '+','-',' ','*','/'};
	int size = 7;

	for(; i<size; i++)
	{
		if(c==priorities[i])
		{
			return i;
		}
	}
	return -1;
} 

// 0 means p1.priority == p2.priority
// 1                    >
// -1                   <
int checkPriority(int p1, int p2)
{
	if(p1-p2==1 || p1-p2==-1 || p1-p2==0)
	{
		return 0;
	}
	else if(p1-p2>1)
	{
		return 1;
	}
	else if(p1-p2 < -1)
	{
		return -1;
	}
}

// transmit infix into postfix.
// attention for operands not being pushed into stack.
void infix2postfix(Stack *s)
{	
	ElementType c, popc, topc;
	char output[255];
	int i = 0;
	int p1, p2;	

	printf("%s", "input the expr: ");
	while((c=getchar()) != '\n')
	{
		if(c=='(') // when the char is ( or )
		{
			push(s, c);
		}
		else if(c==')')
		{
			while(!isEmpty(s) && (topc=getTop(s))!='(')
			{
				pop(s, &popc);
				output[i++] = popc;	
			}
			if(topc=='(')
			{
				pop(s,&popc);
			}
		} // when the char is ( or ) over.

		else if(c >= 'a' && c<='z') // c is an operand.
		{
			output[i++] = c;
		}
		else if((p1=isOperator(c)) != -1) // c is an operator.
		{
			if(isEmpty(s)) // if the stack is empty.
			{
				push(s, c);
			}
			else  // if the stack is not empty.
			{								
				while(!isEmpty(s))
				{
					topc = getTop(s);
					// after that, check priority between c and topc.
					p2 = isOperator(topc);
					if(checkPriority(p1,p2) != 1) // p1.priority <= p2.priority, then pop operand under p2 into output array.
					{
						pop(s, &popc);
						output[i++] = popc;
					}
					else
					{						
						break;
					}
				}	
				push(s, c);
			}			
		}
	}
	while(!isEmpty(s)) // pop surplus elements into output array.
	{
		pop(s, &popc);
		output[i++] = popc;	
	}
	printChatArray(output, i);
}

int main()
{
	Stack s;

	initStack(&s, 1000);
	infix2postfix(&s);
}