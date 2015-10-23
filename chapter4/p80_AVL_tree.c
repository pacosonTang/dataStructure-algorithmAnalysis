#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct AVLTree;
typedef struct AVLTree *AVLTree;

AVLTree createAVLTree(ElementType);
AVLTree makeEmpty(AVLTree);
AVLTree insert(ElementType, AVLTree) ;
AVLTree deleteAVLTree(ElementType e, AVLTree root);
ElementType Retrieve(AVLTree);

AVLTree singleRotateLeftLeft(AVLTree root);
AVLTree singleRotateRightRight(AVLTree root);
AVLTree doubleRotateLeftRight(AVLTree root);
AVLTree doubleRotateRightLeft(AVLTree root);

int getHeight(AVLTree root);

// we adopt child-sibling notation
struct AVLTree
{
	ElementType value;
	AVLTree left;
	AVLTree right;
	int height;
};
//get the maximum
int max(int a, int b)
{
	return  a > b ? a : b;
}

// get the height
int getHeight(AVLTree root)
{
	if(!root)
		return -1;
	else
		return 1 + max(getHeight(root->left), getHeight(root->right));
}

// create a AVLTree with root node
AVLTree createAVLTree(ElementType value)
{	
	AVLTree t;

	t = (AVLTree)malloc(sizeof(struct AVLTree));
    if(!t) {
        Error("out of space, from func createAVLTree");        
        return NULL;
    }    
	t->left = NULL;
	t->right = NULL;	
	t->value = value;
	t->height = 0;
	return t;
}

// make the AVLTree empty 
AVLTree makeEmpty(AVLTree t)
{
	if(t){
		makeEmpty(t->left);
		makeEmpty(t->right);		
		free(t);
	}			
	return NULL;
}

AVLTree doubleRotateLeftRight(AVLTree root) // the case is left-right
{
	AVLTree temp;
	AVLTree right;

	temp = root->left;
	right = temp->right;
	
	root->left = right; // convert left-right into left-left
	temp->right = right->left;
	right->left= temp;
	
	temp->height = getHeight(temp);
	return singleRotateLeftLeft(root);  // the case is left-left
}


AVLTree doubleRotateRightLeft(AVLTree root) // the case is right-left
{
	AVLTree temp;
	AVLTree left;

	temp = root->right;
	left = temp->left;
	
	root->right = left; // convert right-left into right-right
	temp->left = left->right;
	left->right = temp;

	temp->height = getHeight(temp);
	return singleRotateRightRight(root); // the case is right-right		
}

AVLTree singleRotateLeftLeft(AVLTree root) // the case is left-left
{
	AVLTree temp; 
	AVLTree left; 	
	
	left = root->left;

	temp = left->right;
	left->right = root;
	root->left = temp;
	
	//root->height = max(getHeight(root->left), getHeight(root->right)) + 1;		
	root->height = getHeight(root);		
	
	return left;
}

AVLTree singleRotateRightRight(AVLTree root) // the case is right-right
{
	AVLTree temp; 
	AVLTree right; 	
	
	right = root->right;

	temp = right->left;
	right->left = root;
	root->right = temp;
	
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;		
	
	return right;
}

AVLTree insert(ElementType e, AVLTree root) 
{			
	if(!root) {// find the node with its left or right being NULL
		root = createAVLTree(e);
		if(root)  
			return root;					 
		else 
			return NULL;
	}

	if(e > root->value) { 
		root->right = insert(e, root->right); 
		if(getHeight(root->right) - getHeight(root->left) == 2) { // after insertion, we should judge whether the tree is balanced or not
			if(e > root->right->value) // the case is right-right
				root = singleRotateRightRight(root);
			else	// the case is right-left
				root = doubleRotateRightLeft(root);
		}
	}
	else if(e < root->value) { 
		root->left = insert(e, root->left); 
		if(getHeight(root->left) - getHeight(root->right) == 2) { // after insertion, we should judge whether the tree is balanced or not
			if(e < root->left->value) // the case is left-left
				root = singleRotateLeftLeft(root);
			else	// the case is left-right
				root = doubleRotateLeftRight(root);
		}
	}
	else
		Error(" you cannot insert the node into the tree for its value equals to one in the tree");	 

	root->height = max(getHeight(root->left), getHeight(root->right)) + 1; // after insertion, root's height increses one layer
	return root; // dont't forget this line !
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
	printf("\n [the left-left case] test for creating a AVL tree with inserting 3, 2, 1 in trun \n");	

	root = NULL;
	root = insert(3, root);	
	root = insert(2, root);	
	root = insert(1, root);	
	printPreorder(1, root); 
		
	printf("\n [the right-right case] test for inserting node '4' and '5' in turn \n");		
	insert(4, root);
	insert(5, root);
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

	printf("\n [the left-left case] test for inserting node '9' in turn \n");		
	root = insert(9, root);	 
	printPreorder(1, root);   	 

	return 0;
}
 