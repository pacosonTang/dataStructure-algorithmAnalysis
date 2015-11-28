#include "stdio.h"
#include "binaryHeap.h"

int main()
{
	char flags[7] = {'a', 'e', 'i', 's', 't', 'p', 'n'};
	int keys[7] = {10, 15, 12, 3, 4, 13, 1};	
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
	printf("\n====== test of building huffman tree for encoding ======\n");
	printBinaryHeap(bh);		
	
	buildHuffman();
	return 0;
}

// building huffman tree 
void buildHuffman()
{	 
	ElementTypePtr temp;		
	char* codes;
	int off;

	off = 0;
	codes = buildCharArray(off+1);
	temp = buildElement();	

	initElement(temp);
	while(!isEmpty(bh))
	{	
		insertHeap(*temp, bh);		
		initElement(temp);
	}	
	temp->code = '\0';

	printf("\n=== the huffman tree we built just now is follows: ===\n");
	printHuffmanTree(temp, 1);
	printf("\n=== the huffman codes of left subtree ===\n");
	printHuffmanCode(temp->left, 1, off, codes);
	printf("\n=== the huffman codes of right subtree ===\n");
	printHuffmanCode(temp->right, 1, off, codes);
}

void copyCharArray(char *a, char *b, int size)
{
	int i;

	for(i=0; i<=size; i++)
		a[i] = b[i];
}

void printHuffmanTree(ElementTypePtr root, int depth)
{		 
	int i;

	if(root) 
	{   			
        for(i = 0; i < depth; i++)
            printf("    ");     		
		if(root->left!=NULL)		
			printf("%d\n", root->key);		
		else
			printf("%d->%c\n", root->key, root->flag);

        printHuffmanTree(root->left,depth+1); 
        printHuffmanTree(root->right, depth+1); // Attention: there's difference between traversing binary tree and common tree                          
    }
    else 
	{
        for(i = 0; i < depth; i++)
            printf("    ");     
        printf("NULL\n");
    }
}


void printHuffmanCode(ElementTypePtr root, int depth, int off, char *codes)
{	
	int i;	
	char *innerCode = buildCharArray(off+2); 
		
	copyCharArray(innerCode, codes, off);
	if(root) 
	{   
		innerCode[off] = root->code;
		innerCode[++off] = '\0';			

        for(i = 0; i < depth; i++)
            printf("    ");     
		
		if(root->left!=NULL)		
			printf("%d\n", root->key);		
		else
			printf("%d->%c->%s\n", root->key, root->flag, innerCode);

        printHuffmanCode(root->left,depth+1, off, innerCode); 
        printHuffmanCode(root->right, depth+1, off, innerCode); // Attention: there's difference between traversing binary tree and common tree                          
    }
    else 
	{
        for(i = 0; i < depth; i++)
            printf("    ");     
        printf("NULL\n");
    }
}

char *buildCharArray(int size)
{
	char* charArray;

	charArray = (char*)malloc(size * sizeof(char));
	if(!charArray)
	{
		Error("failed buildCharArray, for out of space");
		return NULL;
	}
	
	charArray[0] = '\0';

	return charArray;
}

// initialize the element
void initElement(ElementTypePtr temp)
{
	temp->right = deleteMin(bh);	
	temp->left = deleteMin(bh);	
	temp->key = temp->right->key + temp->left->key;	
	temp->right->code = '1';
	temp->left->code = '0';
}