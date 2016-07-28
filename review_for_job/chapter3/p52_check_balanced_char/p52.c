#include "p52.h"

int checkFile(Stack *s)
{
	FILE *fp;
	ElementType c;
	ElementType popc;

	fp = fopen("D:\\classical_books\\datastructure_alg\\source_code\\chapter3\\p52\\temp.txt", "r");
		
	// only test for round bracket '()', bracket '[]', brace'{}'.
	// do you know the meanings of open brace '{' and close brace '}'.
	while((c=getc(fp)) != EOF)
	{
		if(c == '(' || c == '[' || c == '{')
		{
			push(s, c);
		}
		else if(c == ')' || c == ']' || c == '}')
		{
			pop(s, &popc);
			if(c==')' && popc!= '(')
			{
				 return 0;
			}
			else if(c==']' && popc!= '[')
			{
				 return 0;
			}
			else if(c=='}' && popc!= '{')
			{
				 return 0;
			}
		}
	}

	return 1;
}

int main()
{
	Stack s;
	int result;
	char array[255];

	initStack(&s, 1000);
	result = checkFile(&s);
	printf("%d", result);
}