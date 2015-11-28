#include "binaryHeap.h"

int main()
{
	ElementTypePtr tempBox;
	double tempKey;
	double key[7] = {0.20, 0.50, 0.40, 0.70, 0.10, 0.30, 0.80};	
	int i;

	size = 7;
	initBox(size);
	surplus = buildBasicArray(size, 1.0); // building surplus array to store surplus value
	tempBox = buildSingleElement();
	bh = initBinaryHeap(size + 1);

	for(i=0; i<size; i++)
	{	
		tempBox->key = key[i];
		insertHeap(*tempBox, bh);
	}// building binary heap over

	printBinaryHeap(bh);
	printf("\n");
	while(!isEmpty(bh))	
	{
		tempKey = deleteMin(bh)->key;
		printf("%lf -> ", tempKey);
		firstFixDecrease(tempKey);
	}
	printf("\n");
	printBox(size);
	return 0;
}

void firstFixDecrease(double key)
{
	int i;
	ElementTypePtr box;
	ElementTypePtr temp;

	box = buildSingleElement();
	box->key = key; // build single box with key over

	for(i=0; i<size; i++)
	{
		if(surplus[i] < key)
			continue;	
		else
			break;
	}
	temp = boxes[i]	;
	while(temp->next)					
		temp = temp->next;
	temp->next = box;
	surplus[i] -= key;	
}

void printBox(int size)
{
	int i;
	ElementTypePtr temp;
	
	printf("\n====== results of conducting first fix decrease alg towards{0.2, 0.5, 0.4, 0.7, 0.1, 0.3, 0.8}======\n");
	for(i=0; i<size; i++)
	{
		printf("\nbox[%d]", i+1);
		temp = boxes[i]	;
		while(temp->next)	
		{
			printf("->value[%lf]", temp->next->key);
			temp = temp->next;
		}	
	}
	printf("\n");
}
void initBox(int size)
{	
	int i;	

	boxes = (BoxPtr*)malloc(size * sizeof(BoxPtr));
	if(!boxes)
	{
		Error("failed initBox, for out of space");
		return ;
	}

	for(i=0; i<size; i++)
	{
		boxes[i] = (BoxPtr)malloc(sizeof(Box));
		if(!boxes[i])
		{
			Error("failed initBox, for out of space");
			return ;
		}
		boxes[i]->next = NULL;
	}
}

BasicType* buildBasicArray(int size, BasicType initKey)
{
	BasicType* array;
	int i;

	array = (BasicType*)malloc(size * sizeof(BasicType));
	if(!array)
	{
		Error("failed buildBasicArray, for out of space");
		return NULL;
	}		

	for(i=0; i<size; i++)
		array[i] = initKey;
	return array;
}

BoxPtr buildSingleElement()
{
	ElementTypePtr single;	

	single = (ElementTypePtr)malloc(sizeof(ElementType));
	if(!single)
	{
		Error("failed buildSingleBox, for out of space");
		return NULL;
	}		
	single->next = NULL;

	return single;
}