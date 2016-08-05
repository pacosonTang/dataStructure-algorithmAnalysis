#include "top.h"

BinaryHeap buildHeap(int capacity);
void insert(BinaryHeap heap, ElementType data);
void percolateUp(BinaryHeap heap, ElementType data);
ElementType deleteMin(BinaryHeap heap);
void percolateDown(BinaryHeap heap, int index);
void printBinaryHeap(ElementType *array, int size);
int leftChild(int index);
void swap(ElementType* a, ElementType* b);
int isEmpty(BinaryHeap heap);



