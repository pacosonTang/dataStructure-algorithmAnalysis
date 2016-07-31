#include "balanced_binary_tree.h" 

//get the maximum
int max(int a, int b)
{
	return  a > b ? a : b;
}

 // get the height
int getHeight(AVLTree root)
{
	if(root == NULL)
	{
		return -1;
	}
	else
	{
		return root->height;
	}
}

// left left single rotate
AVLTree left_left_single_rotate(AVLTree root)
{		
	AVLTree temp;

	temp = root; // 1st step
	root = root->left; // 2nd step
	temp->left = root->right; // 3rd step
	root->right = temp; // 4th step
	
	// attention for updating height(key)
	root->right->height = 1 + max(getHeight(root->right->left), getHeight(root->right->right));
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));	
	// updating height over.

	return root;
}

// right_right_single_rotate
AVLTree right_right_single_rotate(AVLTree root)
{		
	AVLTree temp;

	temp = root; // 1st step
	root = root->right; // 2nd step
	temp->right = root->left; // 3rd step
	root->left = temp; // 4th step

	// attention for updating height(key)
	root->left->height = 1 + max(getHeight(root->left->left), getHeight(root->left->right));
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));	
	// updating height over.

	return root;
}

// left right double rotate
AVLTree left_right_double_rotate(AVLTree root)
{
	root->left= right_right_single_rotate(root->left);	
	return left_left_single_rotate(root);
}

// right left double rotate
AVLTree right_left_double_rotate(AVLTree root)
{
	root->right = left_left_single_rotate(root->right);	
	return right_right_single_rotate(root);
}

// insert the node with value into the AVLTree
AVLTree insert(ElementType value, AVLTree root) 
{		
	AVLTree t;

	if(root == NULL)
	{
		t = (AVLTree)malloc(sizeof(struct AVLTree));
		if(t == NULL) 
		{
			Error("out of space, from func insert");        
			return NULL;
		}    
		t->left = NULL;
		t->right = NULL;	
		t->value = value;
		t->height = 0;	 
			
		root = t;
	}
	else
	{
		if(value < root->value)
		{
			root->left = insert(value, root->left);			
			if(getHeight(root->left) - getHeight(root->right) > 1)
			{
				if(value < root->left->value) // left-left single rotate
				{
					root = left_left_single_rotate(root);					
				}
				else  // value > root->left->value; // left-right double rotate
				{
					root = left_right_double_rotate(root);
				}
			}
		}
		else if(value > root->value)
		{
			root->right = insert(value, root->right);
			if(getHeight(root->right) - getHeight(root->left) > 1)
			{
				if(value > root->right->value) // right-right single rotate
				{
					root = right_right_single_rotate(root);					
				}
				else  // value < root->right->value; // right-left double rotate
				{
					root = right_left_double_rotate(root);
				}
			}
		}	
	} 	
	
	root->height = 1 + max(getHeight(root->left), getHeight(root->right)); // attention for updating height (key statement)
	return root;
}  

// analog print directories and files name in the AVLTree, which involves postorder traversal. 
void printPreorder(int depth, AVLTree root)
{			
	int i;
		
	if(root) {		
		for(i = 0; i < depth; i++)
			printf("    ");		
		printf("%d\n", root->value);
		printPreorder(depth + 1, root->left);											
		printPreorder(depth + 1, root->right); // Attention: there's difference between traversing binary tree and common tree							
	}
	else {
		for(i = 0; i < depth; i++)
			printf("    ");		
		printf("NULL\n");
	}
} 
 
int main()
{
	AVLTree root;		

	printf("\n ====== test for building the AVLTree ====== \n");	 		
	printf("\n [the left-left single rotate case] test with inserting 3, 2, 1 in trun \n");	

	root = NULL;
	root = insert(3, root);	
	root = insert(2, root);	
	root = insert(1, root);	
	printPreorder(1, root); 
	
	
	printf("\n [the right-right single rotate case] test with inserting 4 and 5 in turn \n");		
	root = insert(4, root);
	root = insert(5, root);
	printPreorder(1, root); 	 	 

	
	printf("\n [the right-right case] test for inserting node '6 in turn \n");		
	root = insert(6, root);	
	printPreorder(1, root); 
		 	 
	
	printf("\n [the right-right case] test for inserting node '7' and '16' in turn \n");		
	root = insert(7, root);
	root = insert(16, root);
	printPreorder(1, root); 

	
	printf("\n [the right-left case] test for inserting node '15' in turn \n");		
	root = insert(15, root);	 
	printPreorder(1, root); 
		 
	
	printf("\n [the right-left case] test for inserting node '14' in turn \n");		
	root = insert(14, root);	 
	printPreorder(1, root); 	

	
	printf("\n [the right-left case] test for inserting node '13' in turn \n");		
	root = insert(13, root);	 
	printPreorder(1, root); 

	printf("\n [the left-left case] test for inserting node '12' in turn \n");		
	root = insert(12, root);	 
	printPreorder(1, root); 

	printf("\n [the left-left case] test for inserting node '11' and '10' in turn \n");		
	root = insert(11, root);	 
	root = insert(10, root);	 
	printPreorder(1, root); 

	printf("\n [the left-left case] test for inserting node '8' in turn \n");		
	root = insert(8, root);	 
	printPreorder(1, root); 
	
	printf("\n [the left-right case] test for inserting node '9' in turn \n");		
	root = insert(9, root);	 
	printPreorder(1, root);   

	return 0;
}