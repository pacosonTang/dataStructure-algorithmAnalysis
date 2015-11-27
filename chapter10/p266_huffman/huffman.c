#include "stdio.h"
#include "binaryHeap.h"

int main()
{
	char flags[7] = {'a', 'e', 'i', 's', 't', 'p', 'n'};
	int keys[7] = {10, 15, 12, 3, 4, 13, 1};
	int size;
	int i;
	ElementTypePtr single;

	size = 7;	
	bh = initBinaryHeap(2*size);
	single = buildElement();	
	for(i=0; i<size; i++) // insert the flags with coresponding keys into the binary heap
	{
		single->flag = flags[i];
		single->key = keys[i];
		single->left = single->right = NULL;
		insertHeap(*single, bh);		
	}	
	printBinaryHeap(bh);		
	
	buildHuffman();
	return 0;
}

void buildHuffman()
{	 
	ElementTypePtr temp;		

	temp = buildElement();	

	temp->right = deleteMin(bh);	
	temp->left = deleteMin(bh);
	temp->key = temp->right->key + temp->left->key;
	while(!isEmpty(bh))
	{	
		insertHeap(*temp, bh);		
		temp->right = deleteMin(bh);	
		temp->left = deleteMin(bh);
		temp->key = temp->right->key + temp->left->key;		
	}	
	
	printf("\n\t === the huffman tree we built just now is follows: ===\n");
	printHuffman(temp, 1);
}

void printHuffman(ElementTypePtr root, int depth)
{	
	int i;
		
	if(root) 
	{      
        for(i = 0; i < depth; i++)
            printf("    ");     
        printf("%d\n", root->key);
        printHuffman(root->left,depth+1);   
        printHuffman(root->right, depth+1); // Attention: there's difference between traversing binary tree and common tree                          
    }
    else 
	{
        for(i = 0; i < depth; i++)
            printf("    ");     
        printf("NULL\n");
    }
}