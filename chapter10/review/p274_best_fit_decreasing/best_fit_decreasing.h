#include "top.h"

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

// 最佳适合递减算法.(首先遍历箱子，找出该货物存放后，对应箱子的剩余容量最小的箱子)
void best_fit_decreasing(BinaryHeap heap, struct Warehouse warehouse)
{	
	int i, weight, diff;	
	Box temp;
	Box* array = warehouse.array; 
	int minIndex=-1, minValue = SUM;

	// step2: 删除大根堆中最大元素.用删除的元素 添加到 箱子中.
	while(!isEmpty(heap))
	{		
		weight = deleteMin(heap);
		for(i=0; i<warehouse.size;i++) // 遍历仓库中的所有箱子.
		{				
			diff = array[i]->value - weight; // diff 此刻表示差值.
			if(diff>=0 && diff <= minValue) // key if condition.
			{
				minValue = diff;
				minIndex = i;
				if(diff==0) //当差值等于0时，表示最佳的.
				{
					break;
				}
			}
		} // 所有箱子遍历over.
		
		if(minValue == SUM) // 没有找到适合的箱子，需要开辟一个新箱子(size++).
		{
			minIndex = i;
			warehouse.size++;
		}

		// 装货入箱.
		temp = array[minIndex]; 
		while(temp->next)
		{			
			temp = temp->next;
		}	
		temp->next = createGood(weight); 
		if(temp->next) // 如果内存分配成功.
		{
			array[minIndex]->value -= weight;
		} // 装货over.
		//printBoxes(warehouse); // 取消这行注释用于调试.
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