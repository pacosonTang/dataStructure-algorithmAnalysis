#include "first_fit_decreasing.h"

extern BinaryHeap initBinaryHeap(int capacity);
extern void insert(ElementType value, BinaryHeap bh);
extern ElementType deleteMin(BinaryHeap);
extern void printBinaryHeap(BinaryHeap bh);
extern int isEmpty(BinaryHeap bh); 

void main()
{
	int i;
	int goods[] = {2, 5, 4, 7, 1, 3, 8};
	BinaryHeap heap;
	struct Warehouse warehouse;
	
	initWarehouse(&warehouse, ElementNum); //  初始化仓库(箱子数组);

	// step1: 建立大根堆.
	heap = initBinaryHeap(ElementNum+1); // 堆的下标0的元素不用，这是老生常谈了.
	if(heap==NULL)
	{
		return ;
	}
	for(i=0; i<ElementNum; i++)
	{	
		insert(goods[i], heap);
	}
	//step1 over.
	printBinaryHeap(heap);
	
	// step2: 应用首次适合递减算法.
	printf("\n\t === review for first fit decreasing alg ===\n");
	first_fit_decreasing(heap, warehouse);
}