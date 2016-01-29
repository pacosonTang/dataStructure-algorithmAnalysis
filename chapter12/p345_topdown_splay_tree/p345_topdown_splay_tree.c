#include "topdown_splay_tree.h" 

// allocate memory for new node.
Node makeNode(int value)
{
	Node node;

	node = (Node)malloc(sizeof(struct Node));
	if(!node)
	{
		Error("failed makeNode, for out of space !");
		return NULL;
	}
	node->left = NULL;
	node->right = NULL;	
	node->value = value;
	
	return node;
}

// left left single rotate
TopDownSplayTree left_left_single_rotate(TopDownSplayTree root)
{		
	TopDownSplayTree temp;

	temp = root; // 1st step
	root = root->left; // 2nd step
	temp->left = root->right; // 3rd step
	root->right = temp; // 4th step
	
	return root;
}

// right_right_single_rotate
TopDownSplayTree right_right_single_rotate(TopDownSplayTree root)
{		
	TopDownSplayTree temp;

	temp = root; // 1st step
	root = root->right; // 2nd step
	temp->right = root->left; // 3rd step
	root->left = temp; // 4th step	

	return root;
}

// performing splay operations 
TopDownSplayTree topdown_splay(int value, TopDownSplayTree middle)
{
	struct Node plusTree;	
	Node leftTreeMax;	
	Node rightTreeMin;

	leftTreeMax = &plusTree;
	rightTreeMin = &plusTree;

	while(value != middle->value)
	{   
		if(middle->value < value)  // the new node is greater.
		{	 
			if(middle->right == NULL)
			{
				break;
			}
			else if(middle->right->value < value && middle->right->right)
			{
				middle = right_right_single_rotate(middle);
			}			
			leftTreeMax->right = middle;
			leftTreeMax = middle;
			middle = middle->right;		
			leftTreeMax->right = NULL;
		}
		
		if(middle->value > value) // the new node is less.
		{		
			if(middle->left == NULL)
			{
				break;
			}
			else if(middle->left->value > value && middle->left->left)
			{
				middle = left_left_single_rotate(middle);
			}
			rightTreeMin->left = middle;
			rightTreeMin = middle;
			middle = middle->left;
			rightTreeMin->left = NULL;
		}	
	}
	
	leftTreeMax->right = middle->left;
	rightTreeMin->left = middle->right;
	middle->left = plusTree.right;
	middle->right = plusTree.left;

	return middle;
}

// delete the root of the  TopDownSplayTree
TopDownSplayTree deleteNode(int value, TopDownSplayTree root)
{
	TopDownSplayTree newroot;

	if(root == NULL) 
	{
		return root;
	}
	else // the splay tree is not null
	{
		root = topdown_splay(value, root);
		if(root->value == value)  // find the node with given value.
		{ 
			if(root->left == NULL)
			{
				newroot = root->right;
			}
			else
			{
				newroot = root->left;
				// perform splay again with value towards the left subtree which is not null.
				newroot = topdown_splay(value, newroot);
				newroot->right = root->right; 
			}
			free(root);
			root = newroot;
		}		
	}	
	
	return root;
}

// insert the node with value into the TopDownSplayTree
TopDownSplayTree insert(int value, TopDownSplayTree root)
{
	TopDownSplayTree node;
	
	node = makeNode(value);		 
	
	if(root == NULL) // the splay tree is null
	{
		return node;
	}
	else // the splay tree is not null
	{
		root = topdown_splay(value, root);

		if(root->value > value)  
		{
			node->left = root->left;
			node->right = root;
			root->left = NULL;
			root = node;			
		}
		else if(root->value < value)  
		{
			 node->right = root->right;
			 root->right = NULL;
			 node->left = root;			 
			 root = node;
		}
		else			
		{
			return root;
		}
	}	
	
	return root;
}

// test for insert operation.
int main1()
{
	TopDownSplayTree root;	
	int data[] = {5, 11, 23, 10, 17};
	int size = 5;
	int i;
	
	printf("\n === executing insert with {5, 11, 23, 10, 17} in turn.=== \n");
	root = NULL;
	for(i=0; i<size; i++)
	{
		root = insert(data[i], root);
		printPreorder(1, root);	
	} 		

	printf("\n === executing insert with 8 in turn.=== \n");
	root = insert(8, root);
	printPreorder(1, root);		

	printf("\n === executing insert with 18 in turn.=== \n");
	root = insert(18, root);
	printPreorder(1, root);

	return 0;
}

// test for splay operation and deleting operation.
int main()
{	
	TopDownSplayTree root;
	TopDownSplayTree temp;
	
	printf("\n ====== test for splaying operation====== \n");
	printf("\n === original tree is as follows.=== \n");
	root = makeNode(12); // root = 12
	temp = root;
	temp->left = makeNode(5);
	temp->right = makeNode(25);

	temp = temp->right;  // root = 25
	temp->left = makeNode(20);
	temp->right = makeNode(30);

	temp = temp->left;  // root = 20
	temp->left = makeNode(15);
	temp->right = makeNode(24);

	temp = temp->left;  // root = 15
	temp->left = makeNode(13);
	temp->right = makeNode(18);

	temp = temp->right;  // root = 18
	temp->left = makeNode(16);	

	printPreorder(1, root);

	printf("\n === executing splay operation with finding value=19.=== \n");
	root = topdown_splay(19, root);
	printPreorder(1, root);	 

	printf("\n === executing deleting operation with value=15.=== \n");
	root = deleteNode(15, root);
	printPreorder(1, root);	 


	return 0;
}

// analog print node values in the binominal tree, which involves preorder traversal. 
void printPreorder(int depth, TopDownSplayTree root)
{			
	int i;
	
	if(root) 
	{		
		for(i = 0; i < depth; i++)
			printf("    ");
		printf("%d\n", root->value);			
		printPreorder(depth + 1, root->left);									
		printPreorder(depth + 1, root->right);
	} 
	else
	{
		for(i = 0; i < depth; i++)
			printf("    ");
		printf("NULL\n");
	}
} 
