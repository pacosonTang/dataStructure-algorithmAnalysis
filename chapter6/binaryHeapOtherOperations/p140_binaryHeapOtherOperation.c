 #include "binaryheap.h"

#define Infinity 10000
 // switch the elements 
void percolateUp(int index, BinaryHeap bh);

void swap(ElementType *x, ElementType *y)
{
	ElementType temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

// percolating up the element when its value is less than parent
 void percolateUp(int index, BinaryHeap bh)
 {
	int parent;	

	parent = index / 2;
	if(parent == 0 || bh->elements[parent] < bh->elements[index])
		return;
	else
		swap(&bh->elements[parent], &bh->elements[index]); // switch the elements with index index and parent
	
	percolateUp(parent, bh);
}

// percolating down the element when its value is greater than children
 void percolateDown(int index, BinaryHeap bh)
 {	
	int left;
	int right;
	int parent;		

	left = -1;
	right = -1;
	parent = index;

	if(2 * index < bh->size) 
	{
		left = 2 * index;
		right = left + 1;
	}
	else if(2 * index == bh->size)
		left = 2 * index;	
	// valuation for left and right over
	
	if(left == -1 && right == -1)
		return ;
	else if(left != -1 && right == -1) { // the element has the left child	 
		if(bh->elements[parent] > bh->elements[left]) 
			swap(&bh->elements[parent], &bh->elements[left]); // switch the elements with index left and parent					 		
	}		
	else if(left != -1 && right != -1) // the element has two children
	{
		left = bh->elements[left] < bh->elements[right] ? left : right; // get the lesser, the left is just a temp variable not left child
		if(bh->elements[parent] > bh->elements[left])  
			swap(&bh->elements[parent], &bh->elements[left]); // switch the elements with index left(temp variable not left child) and parent					 
	}
	percolateDown(left, bh);	
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
	percolateUp(index, bh);
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
	percolateDown(index, bh);
}

//deleting the element under index 
void deleteElement(int index, BinaryHeap bh)
{
	decreaseKey(index, Infinity, bh); // 1st step, decreaseKey operation placing the element under index upto the root	
	deleteMin(bh); //2nd step, deleteMin deleting the element under the root;
}
 
// building the heap with data in array randomly
void buildHeap(ElementType *data, BinaryHeap bh)
{
	int i;
	
	for(i = 1; i<=bh->size; i++)
		bh->elements[i] = data[i-1];
	for(i = bh->size / 2; i > 0; i--)
		percolateDown(i, bh);
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
	deleteMin(bh);		
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

	printf("\n\t=== test for deleteElement(4, bh) ===\n");
	deleteElement(4, bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for deleteElement(1, bh) ===\n");
	deleteElement(1, bh);
	printBinaryHeap(bh);

	printf("\n\t=== test for deleteElement(3, bh) ===\n");
	deleteElement(3, bh);
	printBinaryHeap(bh);
	 
	printf("\n\t=== test for building heap with {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130} ===\n");
	capacity = 16;
	bh = initBinaryHeap(capacity);
	bh->size = 15;
	buildHeap(buildHeapData, bh);
	printBinaryHeap(bh);

	return 0;
}
