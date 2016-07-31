#include "binary_search_tree.h"

int main()
{
	ElementType data[] = {2, 8, 1, 3, 4};
	int length = 5;
	int i;
	Tree root = createTree(6);
	Tree temp;

	for(i=0;i<length;i++)
	{
		insertTree(root, data[i]);
	}
	printPreorder(root, 1);

	temp = find(root, 8);	
	printf("\nafter find(root, 8), temp->value = %d \n", temp->value);

	temp = findMin(root);	
	printf("\nafter findMin(root), temp->value = %d \n", temp->value);

	temp = findMax(root);	
	printf("\nafter findMax(root), temp->value = %d \n", temp->value);	

	root = deleteTree(root, 2);
	printf("after deleteTree(root, 2) \n");
	printPreorder(root, 1);
}