#include "stack.h"
#include "binary_tree.h"
 
extern void infir_to_postfix();
extern int computeResult(int operand1, int operand2, int operator_);
extern ElementType compute_postfix();
extern Stack operand;
extern int isOperator(char ch);
extern int computeResult(int operand1, int operand2, int operator_);

// building an expr tree for storing postfix expr
BinaryTree postfixToExprTree()
{			
	int value;		
	BinaryTree* treeArray;	
	int size;
	int index;
	ElementType *p;
	int i ;

	size = getTopOfStack(operand) + 1; //get the top of stack, and add 1 to compute size of the stack
	treeArray = (BinaryTree*)malloc(size * sizeof(BinaryTree)); // alloc memory for treeArray
	index = 0; // set the index of treeArray 0 
	
	p = getArray(operand);
	i = 0;
	while(i < getTopOfStack(operand))
	{
		value = *(p+i++);
		if(value == ' ') // if the value equals ' ', continue 
			continue;
		treeArray[index++] = createBinaryTree(value);// for every element need to build tree node
		if(isOperator(value)) // if the value belongs to operator, 
		{	
			index--;						
			insertNode(treeArray[index-1], treeArray[index], 0);			
			insertNode(treeArray[index-2], treeArray[index], 1);
			treeArray[index-2] = treeArray[index];
			index --;
		}		
		// (treeArray+index++) = createBinaryTree(value);// if the value belongs to operand, push the element into the treeArray
	}
	return *treeArray;
}

// preorder the tree
void printPreorder(int depth, BinaryTree root)
{			
	int i;
		
	if(root) {		
		for(i = 0; i < depth; i++)
			printf("    ");		
		printf("%c\n", root->value);
		printPreorder(depth + 1, root->left);											
		printPreorder(depth + 1, root->right); // Attention: there's difference between traversing binary tree and common tree							
	}
	else {
		for(i = 0; i < depth; i++)
			printf("    ");		
		printf("NULL\n");
	}
}
 
// postordering expression tree with operantors and operands to compute the result of these nodes
int postorder_compute_postfix_expr_tree(BinaryTree root)
{	
	int temp1;
	int temp2;

	if(isOperator(root->value)) {						
		temp1 = postorder_compute_postfix_expr_tree(root->left);											
		temp2 = postorder_compute_postfix_expr_tree(root->right); // Attention: there's difference between traversing binary tree and common tree										
		return computeResult(temp1, temp2, root->value);
	}
	else  
		return root->value - 48;	 
}
 

int main()
{		
	BinaryTree bt;

	// 1.convert infix into postfix expr
	printf("\n ====== convert infix into postfix expr ====== \n");
	infir_to_postfix();	// after this func is called over, we get the postfix of the expr
		
	// 2.convert postfix into the expression tree	
	bt = postfixToExprTree();
	printPreorder(1, bt); 

	//3.compute postfix expr stored in the expression tree
	printf("the final result is : %2d \n", postorder_compute_postfix_expr_tree(bt));

	return 0;
}
