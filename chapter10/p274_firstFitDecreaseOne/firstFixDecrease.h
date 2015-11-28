#include <stdio.h>
#include <malloc.h>

#define Error(str) printf("\n\t error: %s\n", str)
#define BasicType double

int size;
struct Box;
typedef struct Box Box;
typedef struct Box* BoxPtr;

struct Box
{
	double key;
	BoxPtr next;
};

void initBox(int size);
BasicType* buildBasicArray(int size, BasicType firstkey);
void printBox(int);
void firstFixDecrease(double key);

BoxPtr* boxes;
double* surplus;

