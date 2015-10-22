#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct BinarySearchTree;
typedef struct BinarySearchTree *BinarySearchTree;

BinarySearchTree createBinarySearchTree(ElementType);
BinarySearchTree makeEmpty(BinarySearchTree);
BinarySearchTree insert(ElementType, BinarySearchTree) ;
BinarySearchTree deleteBinarySearchTree(ElementType, BinarySearchTree);

// we adopt child-sibling notation
struct BinarySearchTree
{
	ElementType value;
	BinarySearchTree left;
	BinarySearchTree right;
};

// create a BinarySearchTree with root node
BinarySearchTree createBinarySearchTree(ElementType value)
{	
	BinarySearchTree t;

	t = (BinarySearchTree)malloc(sizeof(struct BinarySearchTree));
    if(!t) {
        Error("out of space, from func createBinarySearchTree");        
        return NULL;
    }    
	t->left = NULL;
	t->right = NULL;	
	t->value = value;
	
	return t;
}

// make the BinarySearchTree empty 
BinarySearchTree makeEmpty(BinarySearchTree t)
{
	if(t){
		makeEmpty(t->left);
		makeEmpty(t->right);		
		free(t);
	}			
	return NULL;
}
 
BinarySearchTree insert(ElementType e, BinarySearchTree root) 
{			
	if(!root) {// find the node with its left or right being NULL
		root = createBinarySearchTree(e);
		if(root)
			return root;
		else 
			return NULL;
	}
	if(e > root->value)  // the tree node with value e inserting into right child of the parent 
		root->right = insert(e, root->right);	 
	else if(e < root->value)  // the tree node withe value e inserting into left child of the parent 		
		root->left = insert(e, root->left);	
	else
		Error(" you cannot insert the node into the tree for its value equals to one in the tree");

	return root; // dont't forget this line !
}

// find the BinarySearchTree root node with value equaling to e
//Attention: the first statement must judge whether root is NULL or not
BinarySearchTree find(ElementType e, BinarySearchTree root)
{		
	if(!root) // judge whether root is NULL or not
		return NULL;

	if(e > root->value)
		return find(e, root->left);	
	else if(e < root->value)
		return find(e, root->left);
	else 
		return root;
} 

// find the minimum, (Attention for its non-recursion implementation )
BinarySearchTree findMin(BinarySearchTree root)
{
	if(root) {
		if(root->left)
			return findMin(root->left);
		else
			return root;
	}	 
	return NULL;
}


// find the Maximum, (Attention for its non-recursion implementation )
BinarySearchTree findMax(BinarySearchTree root)
{
	if(root) {
		if(root->right)
			return findMax(root->right);
		else
			return root;
	}	 
	return NULL;
}

// delete the node with given value e from the binary search tree
BinarySearchTree deleteBinarySearchTree(ElementType e, BinarySearchTree root)
{
	BinarySearchTree temp;

	if(!root)
		Error(" elements not found, from func deleteBinarySearchTree ");
	
	if(e > root->value) 
		root->right = deleteBinarySearchTree(e, root->right);
	else if(e < root->value) 
		root->left = deleteBinarySearchTree(e, root->left);
	else {// the value of root equals given e
		if(root->left && root->right) { // if the deleting node has both left and right
			root->value = findMin(root->right)->value; // set root's value the minimum of right tree of root
			root->right = deleteBinarySearchTree(root->value, root->right);			
		}		
		else { // one or zero child is not NULL
			// root->left = deleteBinarySearchTree(root->value, root->left);						
			if(root->right) { // if root->right doesn't equal to NULL
				temp = root;
				root = root->right;
				free(temp);												
			}
			else if(root->left){ // if root->left doesn't equal to NULL
				temp = root;
				root = root->left;
				free(temp);				
			}
			else { // if both root->left and root->right equal to NULL
				free(root);
				root = NULL;
			}
		}
		/* you can also fabricate code like this, which is reshipped from data_structure book
			temp = root;
			if(!root->right)
				root = root->left;
			else if(!root->left)
				root = root->right;
			free(temp);
		*/
	}	
	return root;
}

// analog print directories and files name in the BinarySearchTree, which involves postorder traversal. 
void printPreorder(int depth, BinarySearchTree root)
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
	BinarySearchTree bst;	
	int value[] = {2, 8, 1, 5, 3, 4};
	int i;

	printf("\n ====== test for preordering the BinarySearchTree ====== \n");	 	
	
	printf("\n test for creating a binary search tree with root value 6 \n");	
	bst = createBinarySearchTree(6);
	printPreorder(1, bst); 
		
	printf("\n test for insertint 6 nodes, that's  2, 8, 1, 5, 3 and 4 in turn \n");		
	for(i = 0; i < 6; i++)
		insert(value[i], bst);		
	printPreorder(1, bst); 	 	 

	printf("\n test for find minimum \n");		
	printf(" the minimum is %2d, in this binary search tree! \n", findMin(bst)->value);

	printf("\n test for find maximum \n");		
	printf(" the maximum is %2d, in this binary search tree! \n", findMax(bst)->value);

	printf("\n test for deleting node '2' with two nodes from the binary search tree \n");		
	deleteBinarySearchTree(2, bst);
	printPreorder(1, bst); 	 	 

	printf("\n test for deleting node '5' with one node from the binary search tree \n");		
	deleteBinarySearchTree(5, bst);
	printPreorder(1, bst); 	 	 

	printf("\n test for deleting node '8' with zeron node from the binary search tree \n");		
	deleteBinarySearchTree(8, bst);
	printPreorder(1, bst); 	 	 
	
	printf("\n test for inserting '8', '5' and '2' into the binary search tree \n");		
	insert(8, bst);
	insert(5, bst);
	insert(2, bst);
	printPreorder(1, bst); 	 	 

	return 0;
}
