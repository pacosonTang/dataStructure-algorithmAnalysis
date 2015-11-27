#include <stdio.h>

struct Tree;
typedef struct Tree Tree;
typedef struct Tree* TreePtr;

struct Tree
{
	int flag;
	int key;
	TreePtr left;
	TreePtr right;
};

void buildHuffman();
void printHuffman();