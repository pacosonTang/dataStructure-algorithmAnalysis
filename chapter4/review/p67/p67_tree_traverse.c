#include "child_sibling_general_tree_traverse.h"

// this test is not for binary trees but just general trees.
int main()
{
	Tree root = createTree('/');
	
	// root == '/'
	insertTree(root, createTree('A'));
	insertTree(root, createTree('B'));
	insertTree(root, createTree('C'));
	
	// root == 'A' 
	insertTree(root->child, createTree('D'));
	insertTree(root->child, createTree('E'));
	
	// root == 'B'
	insertTree(root->child->sibling, createTree('F'));
	insertTree(root->child->sibling, createTree('G'));

	// root == 'C'
	insertTree(root->child->sibling->sibling, createTree('H'));
	insertTree(root->child->sibling->sibling, createTree('I'));
	insertTree(root->child->sibling->sibling, createTree('J'));

	// root == 'D'
	insertTree(root->child->child, createTree('K'));

	// preorder + postorder but no inorder towards general trees.
	printf("\n=== preorder ===\n");
	printPreorder(root, 1);	 

	printf("\n=== postorder ===\n");
	printPostorder(root, 1);

	printf("\n");
}