#include "top.h"

// Attention: 如果不把 数组的大小设置为 ElementNum-2+1， 则数组内容会莫名其妙；
// 如 ElementNum=7， 则其最大高度为5，即如果数组的5个空间都用完的话，则没有空间存放 '\0'，puts(str) 的时候 会莫名其妙的多些字符.
char code[ElementNum-2+1]; 
struct HuffmanCode codes[ElementNum];
int counter=0;

void copyCodes(char* src, char* des);

// traverse the huffman tree in preorder.
void printPreorder(HeapNode root, int depth)
{	
	int i = 0;

	for(;i<depth;i++)
	{
		printf("    ");
	}	
	if(root==NULL)
	{
		printf("NULL\n");
	}
	else if(root != NULL) 
	{		
		printf("%d \n", root->value);
		printPreorder(root->left, depth+1);
		printPreorder(root->right, depth+1);
	}
} 

// (递归实现)记录每个字符的哈夫曼编码；root == 哈夫曼树根, depth == 树的深度, 从0开始取.
void huffmanCodeRecursion(HeapNode root, int depth)
{			
	if(root->left)
	{
		code[depth] = '0';
		code[depth+1] = '\0';
		huffmanCodeRecursion(root->left, depth+1);
	}

	if(root->right)
	{
		code[depth] = '1';
		code[depth+1] = '\0';
		huffmanCodeRecursion(root->right, depth+1);
	}	
	else
	{		
		codes[counter].flag = root->flag;
		copyCodes(code, codes[counter++].code);		
		// printf("%s\n", code); // 取消本行注释可以调试程序.
	}
}

// 将 src 中的内容 copy 到 des 中.
void copyCodes(char* src, char* des)
{
	int i;
	
	for(i=0; i<ElementNum-2; i++)
	{
		des[i] = src[i];
	}
}