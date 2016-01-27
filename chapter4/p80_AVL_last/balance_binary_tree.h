#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct AVLTree;
typedef struct AVLTree *AVLTree;

AVLTree insert(ElementType, AVLTree) ;

AVLTree left_left_single_rotate(AVLTree root);
AVLTree right_right_single_rotate(AVLTree root);
AVLTree left_right_double_rotate(AVLTree root);
AVLTree right_left_double_rotate(AVLTree root);

int getHeight(AVLTree root);

// we adopt child-sibling notation
struct AVLTree
{
	ElementType value;
	AVLTree left;
	AVLTree right;
	int height;
};