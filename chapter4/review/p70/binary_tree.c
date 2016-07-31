#include "binary_tree.h"

int main()
{
	Tree root = createTree('/');
	
	// root == '/'
	insertTree(root, createTree('A'), 0);
	insertTree(root, createTree('B'), 1);	
	
	// root == 'A' 
	insertTree(root->left, createTree('C'), 0);
	insertTree(root->left, createTree('D'), 1);
	
	// root == 'B'
	insertTree(root->right, createTree('E'), 0);
	insertTree(root->right, createTree('F'), 1);

	// root == 'C'
	insertTree(root->left->left, createTree('G'), 1);

	// root == 'D'
	insertTree(root->left->right, createTree('I'), 0);

	// preorder + inorder + postorder.
	printf("\n=== preorder ===\n");
	printPreorder(root, 1);	 

	printf("\n=== inorder ===\n");
	printInorder(root, 1);	 

	printf("\n=== postorder ===\n");
	printPostorder(root, 1);
}
