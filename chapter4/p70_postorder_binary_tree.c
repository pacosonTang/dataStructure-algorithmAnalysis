#include <stdio.h>
#include <malloc.h>

#define ElementType char
#define Error(str) printf("\n error: %s \n",str)   

struct BinaryTree;
typedef struct BinaryTree *BinaryTree;

BinaryTree createBinaryTree();
BinaryTree makeEmpty(BinaryTree t);
BinaryTree insert(ElementType e, BinaryTree t, int);

// we adopt child-sibling notation
struct BinaryTree
{
	ElementType value;
	BinaryTree left;
	BinaryTree right;
};

// create a BinaryTree with root node
BinaryTree createBinaryTree()
{	
	BinaryTree t;

	t = (BinaryTree)malloc(sizeof(struct BinaryTree));
    if(!t) {
        Error("out of space, from func createBinaryTree");        
        return NULL;
    }    
	t->left = NULL;
	t->right = NULL;	
	t->value = '/';
	
	return t;
}

// make the BinaryTree empty 
BinaryTree makeEmpty(BinaryTree t)
{
	if(t){
		makeEmpty(t->left);
		makeEmpty(t->right);		
		free(t);
	}			
	return NULL;
}

//insert a Tree node with value e into left child or right child of the parent
BinaryTree insert(ElementType e, BinaryTree parent, int isLeft)
{	
	BinaryTree node;
	
	if(!parent){
		Error("for parent BinaryTree node is empty , you cannot insert one into the parent node, from func insert");        
        return NULL;
	}

	node = (BinaryTree)malloc(sizeof(struct BinaryTree));
	if(!node) {
        Error("out of space, from func insert");        
        return NULL;
    }
	node->value = e;
	node->right = NULL;
	node->left = NULL;// building the node with value e over

	if(isLeft) { // the tree node inserting into left child of the parent 
		if(parent->left) {
			Error("for parent has already had a left child , you cannot insert one into the left child, from func insert");        
			return NULL;	
		}
		parent->left = node;
	}
	else { // the tree node inserting into right child of the parent 
		if(parent->right) {
			Error("for parent has already had a right child , you cannot insert one into the right child, from func insert");        
			return NULL;	
		}
		parent->right = node;
	}	 
	return node;	
}

// find the BinaryTree root node with value equaling to e
BinaryTree find(ElementType e, BinaryTree root)
{
	BinaryTree temp;

	if(root == NULL)
		return NULL;
	if(root->value == e)
		return root;

	temp = find(e, root->left);	
	if(temp) 
		return temp;
	else
		return 	find(e, root->right);				
}

// analog print directories and files name in the BinaryTree, which involves postorder traversal. 
void printPostorder(int depth, BinaryTree root)
{			
	int i;
		
	if(root) {						
		printPostorder(depth + 1, root->left);											
		printPostorder(depth + 1, root->right); // Attention: there's difference between traversing binary tree and common tree
		for(i = 0; i < depth; i++)
			printf("    ");		
		printf("%c\n", root->value);					
	}
	else {
		for(i = 0; i < depth; i++)
			printf("    ");		
		printf("NULL\n");
	}
}

int main()
{
	BinaryTree BinaryTree;

	BinaryTree = createBinaryTree();
	printf("\n ====== test for postordering the BinaryTree presented by left_right_child structure  ====== \n");	 

	
	printf("\n test for respectively inserting 'A' and 'B' into left and right child of the parent '/' , then 'C' and 'D' into the left and right child of the parent 'A' \n");	
	insert('A', find('/', BinaryTree), 1);	// 1 means left child
	insert('B', find('/', BinaryTree), 0);	// 0 means right child
	insert('C', find('A', BinaryTree), 1);
	insert('D', find('A', BinaryTree), 0);
	printPostorder(1, BinaryTree);
	
	printf("\n test for respectively inserting 'A' and 'B' into left and right child of the parent '/' \n");	
	insert('E', find('/', BinaryTree), 1);
	insert('F', find('/', BinaryTree), 0);
	printPostorder(1, BinaryTree); 

	printf("\n test for inserting 'E' into the right child of the  parent 'B' , then repectively 'F' and 'G' into the left and right child of the parent 'H' \n");	
	insert('E', find('B', BinaryTree), 0);		
	insert('F', find('E', BinaryTree), 1);
	insert('G', find('E', BinaryTree), 0);
	printPostorder(1, BinaryTree); /**/

	return 0;
}

 
