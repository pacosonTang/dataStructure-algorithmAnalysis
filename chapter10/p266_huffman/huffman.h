#include <stdio.h>

struct Tree;
typedef struct Tree Tree;
typedef struct Tree* TreePtr;

struct Tree
{
	int flag;
	int key;
	char code;
	TreePtr left;
	TreePtr right;
};

void buildHuffman();
void printHuffmanCode(TreePtr root, int depth, int len, char *codes);
void printHuffmanTree(TreePtr root, int depth);

// allocate memory to build char array with size
char *buildCharArray(int size);

int size;
