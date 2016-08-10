#include "top.h"

void first_fit_decreasing(BinaryHeap heap, struct Warehouse warehouse);
extern ElementType deleteMin(BinaryHeap);
extern void printBinaryHeap(BinaryHeap bh);
extern int isEmpty(BinaryHeap bh); 
void printBoxes(struct Warehouse warehouse);

// 初始化 箱子数组.
Box* initBoxes(int size)
{
	int i;
	Box* array = (Box*)malloc(size * sizeof(Box));

	if(!array)
	{
		Error("failed initBoxes() for out of space.");
		return NULL;
	}
	for(i=0; i<size; i++)
	{
		array[i] = (Good)malloc(sizeof(struct Good));
		if(!array[i])
		{
			Error("failed initBoxes() for out of space.");
			return NULL;
		}
		array[i]->value = SUM; // 剩余容量，初始状态为10. 自定义.
		array[i]->next = NULL;
	}
	return array;
}

void initWarehouse(struct Warehouse* warehouse, int capacity)
{	
	warehouse->capacity = capacity;
	warehouse->size = 0;
	warehouse->array = initBoxes(capacity);		
}

// 为货物分配空间，value==货物重量.
Good createGood(int value)
{
	Good good = (Good)malloc(sizeof(struct Good));
	if(good==NULL)
	{
		Error("failed createGood for out of space.");
		return NULL;
	}
	good->value = value;
	good->next = NULL;
	return good;
}

// 首次适合递减算法.(把物品放入能够盛下它的第一个箱子中)
void first_fit_decreasing(BinaryHeap heap, struct Warehouse warehouse)
{	
	int i, weight;	
	Good temp;
	Box* array = warehouse.array; 
	
	// step2: 删除大根堆中最大元素.用删除的元素 添加到 箱子中.
	while(!isEmpty(heap))
	{
		i=0;
		weight = deleteMin(heap);						
		while(weight > array[i++]->value);
		
		if(array[i-1]->value == SUM)
		{
			warehouse.size++;
		}

		temp = array[i-1]; // 因为上面的 while循环多加了一个1.
		while(temp->next)
		{			
			temp = temp->next;
		}	
		temp->next = createGood(weight); // 因为i 自加了一次, 所以要减1.
		if(temp->next) // 如果内存分配成功.
		{
			array[i-1]->value -= weight;
		}
	}
	printBoxes(warehouse);
}

void printBoxes(struct Warehouse warehouse)
{
	int i;
	Box* array = warehouse.array;
	Good temp;
	
	printf("\n");
	for(i=0; i<warehouse.size; i++)
	{		
		printf("box[%d] = ", i+1);
		temp = array[i];
		while(temp->next)
		{
			printf("%d ", temp->next->value);
			temp = temp->next;			
		}
		printf("\n");
	}
}