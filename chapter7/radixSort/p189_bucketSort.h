#include <stdio.h>
#include <malloc.h>

#define MAX 10
#define ElementType int
#define Error(str) printf("\n\t error: %s \n",str) 

struct Node;
typedef struct Node *Node;

Node *initBuckets();
void bucketSort(Node* buckets, ElementType data, int index);
void radixSort(Node* buckets, ElementType* data, int size);
void bucketsToData(Node* buckets, ElementType *data);
void printBuckets(Node* data);
void printArray(ElementType data[], int size);
Node makeEmpty();

struct  Node
{
	int value;
	Node next;
};