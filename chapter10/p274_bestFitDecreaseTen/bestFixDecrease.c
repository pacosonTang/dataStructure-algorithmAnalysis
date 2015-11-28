#include "binaryHeap.h"

int main()
{
	ElementTypePtr tempBox;
	int tempKey;
	int key[7] = {2, 5, 4, 7, 1, 3, 8};	
	int i;

	size = 7;
	initBox(size);
	surplus = buildBasicArray(size, 10); // building surplus array to store surplus value
	tempBox = buildSingleElement();
	bh = initBinaryHeap(size + 1);

	for(i=0; i<size; i++)
	{	
		tempBox->key = key[i];
		insertHeap(*tempBox, bh);
	}// building binary heap over
		
	printBinaryHeap(bh);
	printf("\n");
	printf("\n===the sequence deleting minimum from binary heap===\n");
	while(!isEmpty(bh))	
	{
		tempKey = deleteMin(bh)->key;
		printf("%d -> ", tempKey);
		bestFixDecrease(tempKey);
	}
	printf("\n");
	printBox(size);
	return 0;
}

void bestFixDecrease(int key)
{
	int i;
	ElementTypePtr box;
	ElementTypePtr temp;
	int minimum;
	int miniIndex;

	box = buildSingleElement();
	box->key = key; // build single box with key over
	miniIndex = 0;
	minimum = 10;

	for(i=0; i<size; i++)
	{
		if(surplus[i] < key)
			continue;
		if(surplus[i] - key < minimum)
		{
			minimum = surplus[i] - key;
			miniIndex = i;
		}
	}

	temp = boxes[miniIndex]	;
	while(temp->next)					
		temp = temp->next;
	temp->next = box;
	surplus[miniIndex] -= key;	
}

void printBox(int size)
{
	int i;
	ElementTypePtr temp;
	
	printf("\n====== results of conducting best fix decrease alg towards{2, 5, 4, 7, 1, 3, 8}======\n");
	for(i=0; i<size; i++)
	{
		printf("\nbox[%d]", i+1);
		temp = boxes[i]	;
		while(temp->next)	
		{
			printf("->value[%d]", temp->next->key);
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