#include "infix2postfix.h" 

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
		 
	return 0;
}