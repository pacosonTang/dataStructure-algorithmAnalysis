#include <stdio.h>
#include <malloc.h>

#define Error(str) printf("\n\t error: %s\n", str)
#define BasicType int

int size;
struct Box;
typedef struct Box Box;
typedef struct Box* BoxPtr;

struct Box
{
	int key;
	BoxPtr next;
};

void initBox(int size);
BasicType* buildBasicArray(int size, BasicType firstkey);
void printBox(int);
void firstFixDecrease(int key);

BoxPtr* boxes;
int* surplus;

