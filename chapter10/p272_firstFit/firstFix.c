#include "firstFix.h"

#define ElementType Box
#define ElementTypePtr BoxPtr

int main()
{
	double key[7] = {0.2, 0.5, 0.4, 0.7, 0.1, 0.3, 0.8};	
	int i;

	size = 7;
	initBox(size);
	surplus = buildBasicArray(size, 1.0); // building surplus array to store surplus value
	
	for(i=0; i<size; i++)
		firstFix(key[i]);
		
	printBox(size);

	return 0;
}

void firstFix(double key)
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
		temp = boxes[i]	;
		while(temp->next)					
			temp = temp->next;
		temp->next = box;
		surplus[i] -= key;
		break;
	}
}

void printBox(int size)
{
	int i;
	ElementTypePtr temp;
	
	printf("\n====== results of conducting first fix alg towards{0.2, 0.5, 0.4, 0.7, 0.1, 0.3, 0.8}======\n");
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