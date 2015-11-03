 #include "binaryheap.h"

#define Infinity 10000
 // switch the elements 

void swap(ElementType *x, ElementType *y)
{
	ElementType temp;

	temp = *x;
	*x = *y;
	*y = temp;
}
 
// get the parent of the element with index 
int parentFromOne(int index)
{
	return index / 2;
}

// percolating up the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateUpFromOne(int index, BinaryHeap bh)
 {	
	ElementType *data;
	ElementType temp;
	int size;	
	int parent;
		
	data = bh->elements;
	size = bh->size;
	
	for(temp = data[index]; parentFromOne(index) > 0; index = parent)
	{
		parent = parentFromOne(index);
		if(parent == 0 || temp > data[parent])		 		
			break;
		else		
			data[index] = data[parent];					 						
	}
	data[index] = temp;
 }
 
 // get the left child of node under index with startup one
int leftChildFromOne(int index)
{
	return index * 2;
}
 
// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 1
 void percolateDownFromOne(int index, BinaryHeap bh)
 {	
	ElementType *data;
	int size;
	ElementType temp;
	int child;

	data = bh->elements;
	size = bh->size;

	for(temp = data[index]; leftChildFromOne(index) <= size; index = child)
	{
		child = leftChildFromOne(index);
		if(child < size && data[child] > data[child+1])
			child++;
		if(temp > data[child])
			data[index] = data[child];
		else
			break;
	}
	data[index] = temp;
 }

//decreasing value of the element under index by increment
void decreaseKey(int index, ElementType decrement, BinaryHeap bh)
{	
	if(index > bh->size || index < 1)
	{
		Error(" failed decreaseKey, since overstep the boundary! ");
		return ;
	}

	bh->elements[index] -= decrement; // update the element under given index
	percolateUpFromOne(index, bh);
}

//increasing value of the element under index by increment
void increaseKey(int index, ElementType increment, BinaryHeap bh)
{	
	if(index > bh->size || index < 1)
	{
		Error(" failed increaseKey, since overstep the boundary! ");
		return ;
	}

	bh->elements[index] += increment; // update the element under given index
	percolateDownFromOne(index, bh);
}

//deleting the element under index 
void deleteElement(int index, BinaryHeap bh)
{
	decreaseKey(index, Infinity, bh); // 1st step, decreaseKey operation placing the element under index upto the root	
	deleteMin(bh); //2nd step, deleteMin deleting the element under the root;
} 

// get the left child of node under index with startup zero
int leftChildFromZero(int index)
{
	return index * 2 + 1;
}
 
// percolating down the element when its value is greater than children (minimal heap)
 //Attention: all of bh->elements starts from index 0
 void percolateDownFromZero(int index, BinaryHeap bh)
 {	
	ElementType *data;
	ElementType temp;
	int size;	
	int child;

	data = bh->elements;
	size = bh->size;

	for(temp = data[index]; leftChildFromZero(index) < size; index = child)
	{
		child = leftChildFromZero(index);
		if(child < size - 1 && data[child] > data[child+1])
			child++;
		if(temp > data[child])
			data[index] = data[child];
		else
			break;
	}
	data[index] = temp;
}

// building the heap with data in array randomly
void buildHeap(BinaryHeap bh)
{
	int i;	
	ElementType *data;

	data = bh->elements;
	
	for(i = bh->size/2; i >= 0; i--)
		percolateDownFromZero(i, bh);		
}

 int main()
{
	ElementType data[] = {85, 80, 40, 30, 10, 70, 110}; // P141	
	ElementType buildHeapData[] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
	BinaryHeap bh;	
	int size;
	int i;	
	int capacity;
	
	printf("\n\t=== test for inserting the binary heap with {85, 80, 40, 30, 10, 70, 110} in turn ===\n");
	capacity = 14;
	bh = initBinaryHeap(capacity);
	size = 7;	
	
	
	for(i = 0; i < size; i++)
		insert(data[i], bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for inserting the binary heap with {100, 20, 90} in turn ===\n");
	insert(100, bh);
	insert(20, bh);
	insert(90, bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for inserting the binary heap with 5 ===\n");
	insert(5, bh);		
	printBinaryHeap(bh);

	printf("\n\t=== test for 3 deletings towards the minimum in binary heap ===\n");
	deleteMin(bh);	
	printBinaryHeap(bh);
	deleteMin(bh);		
	printBinaryHeap(bh);
	deleteMin(bh);	
	printBinaryHeap(bh);

	// other operations in bianry heap	
	printf("\n\t====== test for other operations in bianry heap as follows ======\n");
	printf("\n\t=== test for increaseKey(4, 120, bh) ===\n");
	increaseKey(4, 120, bh);
	printBinaryHeap(bh);
	
	printf("\n\t=== test for increaseKey(2, 120, bh) ===\n");
	increaseKey(2, 120, bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for decreaseKey(9, 195, bh) ===\n");
	decreaseKey(9, 195, bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for decreaseKey(4, 90, bh) ===\n");
	decreaseKey(4, 90, bh);
	printBinaryHeap(bh);
	

	printf("\n\t=== test for decreaseKey(7, 50, bh) ===\n");
	decreaseKey(7, 50, bh);
	printBinaryHeap(bh);
	
	printf("\n\t=== test for decreaseKey(5, 155, bh) ===\n");
	decreaseKey(5, 155, bh);
	printBinaryHeap(bh);



	printf("\n\t=== test for deleteElement(4, bh) ===\n");
	deleteElement(4, bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for deleteElement(1, bh) ===\n");
	deleteElement(1, bh);
	printBinaryHeap(bh);

	
	printf("\n\t=== test for deleteElement(3, bh) ===\n");
	deleteElement(3, bh);
	printBinaryHeap(bh); // test over , Bingo!
	 
	// as you know, the build heap operation is identical with other operations
	printf("\n\t=== test for building heap with {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130} ===\n");
	capacity = 16;
	bh = initBinaryHeap(capacity);
	bh->size = 15;
	bh->elements = buildHeapData; 
	buildHeap(bh);
	printBinaryHeapFromZero(bh);

	return 0;
}
