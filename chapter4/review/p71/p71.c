#include "infix2postfix.h"
#include "binary_tree.h"

// compute the final value of given postfix.
void computePostfix(Stack s, int *postfix, int length)
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

int index = 0;
// transmit the expr tree into postfix updated from printPostfix().
void exprTree2postfix(Tree root, int* postfix)
{				
	if(root != NULL) 
	{				
		exprTree2postfix(root->left, postfix);
		exprTree2postfix(root->right, postfix);
		//printf("%c\n", root->value);
		postfix[index++] = root->value;
	}	
}

// build a tree with given postfix.
Tree buildTree(int *postfix, int length)
{
	Tree* root; // array of Tree node.	
	int i=0, invalid = 0;	 // invalid presents how many units in root are used.

	root = (Tree*)malloc(sizeof(Tree) * length);
	if(root==NULL)
	{
		ERROR("error: failed buidlTree for there is no spare space.");
		return NULL;
	}

	for(i=0; i<length; i++)
	{
		root[invalid] = createTree(postfix[i]);  // create a tree node with postfix[i].				
		if(isOperator(postfix[i]) != -1)// postfix[i] is an operand.(also operations based on stack)
		{				
			root[invalid]->right = root[invalid-1];			
			root[invalid]->left = root[invalid-2];
			root[invalid-2] = root[invalid];
			invalid--;
		}
		else // postfix[i] is an operator.
		{
			invalid++;
		}		
	}
	return root[0];
}

int main()
{	
	Stack s;
	int length;
	int output[255];
	int postfix[255];
	Tree root;
	
	s = initStack(100);	
	if(s==NULL)
	{
		return -1;
	}
		
	// step1: user type infix expr
	// step2: switch infix into postfix
	length = infix2postfix(s, output); //switch infix into postfix.	
	printf("postfix are as follows: ");
	printChatArray(output, length); // print postfix expr.
	
	// step3: build a expr tree with postfix.	
	root = buildTree(output, length);
	printPreorder(root, 1);

	// step4: compute the value of postfix expr.	
	// step4.1: convert expr tree into postfix.
	exprTree2postfix(root, postfix);
	printf("convert expr tree into postfix: ");
	printChatArray(postfix, index);
	
	//step4.2: compute postfix expr.
	reset(s);
	computePostfix(s, postfix, index);
	return 0;
}