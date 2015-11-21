#include <stdio.h>
#include "binaryheap.h"

// allocate memory for the vertexes with size
Vertex* makeEmptyVertexes(int size)
{
	Vertex *array; 
	int i;

	array = (Vertex*)malloc(size * sizeof(Vertex)); 
	if(!array)
	{
		Error("out of space, from func makeEmptyVertexes");
		return NULL;
	} 
	
	// initializing the set index towards every vertex with its array index
	for(i = 1; i <= size; i++)
		array[i-1] = -i;

	return array;
}

void printParent(Vertex* vertexes, int size)
{
	int i;
	
	printf("\n\n\t the parent of every vertex at a glance");
	for(i=0; i<size; i++)
		printf("\n\t parent[%d] = %d", i, vertexes[i]);
}

int find(Vertex *parent, Vertex single)
 {
	while (single >= 0)
		single = parent[single]; 
	return single;
}

//judge whether the vertex index is the parent or not, also 1 or 0
//if the vertex under index is not the parent ,that's to say its parent is one of other vertexes
int isParent(Vertex *parent, Vertex index)
{
	return parent[index] == -index-1;
}

void setUnion(Vertex *parent, Vertex start, Vertex end)
{	
	if(isParent(parent, start) ) // start is the parent 
	{
		if(!isParent(parent, end)) // but end is not the parent
			end = find(parent, end) + 1; // find the parent of end
		parent[start] = end;		
	}
	
	else // start is not the parent 
	{
		start = -find(parent, start) - 1; // find the parent of start
		if(!isParent(parent, end)) // but end is not the parent
			end = find(parent, end) + 1; // find the parent of end
		parent[end] = start;
	}
}

void kruskal(BinaryHeap bh, int vertexNum)
{
	int counter;
	int set1;
	int set2; 
	Vertex start;
	Vertex end;
	Vertex* parent;
	ElementType singleEdge;	

	counter = 0;	
	parent = makeEmptyVertexes(vertexNum);

	while(counter < vertexNum - 1)
	{
		singleEdge = deleteMin(bh);
		start = singleEdge.start;
		end = singleEdge.end;
		set1 = find(parent, start);
		set2 = find(parent, end);// find the set of vertex start and end
		
		if(set1 != set2)
		{				
			setUnion(parent, start, end);
			counter++;
			printf("\n\t weight(v%d,v%d) = %d", singleEdge.start+1, singleEdge.end+1, singleEdge.weight);
		}		
	}
	printParent(parent, vertexNum);
	printf("\n\n\t");
}

int main()
{  
	BinaryHeap bh;
	ElementTypePtr temp;	
	int vertexNum;
	int size = 7;
	int capacity;
	int i;
	int j;	
	 
	int adjTable[7][7] = 
	{
		{0, 2, 4, 1, 0, 0, 0},
		{2, 0, 0, 3, 10, 0, 0},
		{4, 0, 0, 2, 0, 5, 0},
		{1, 3, 2, 0, 7, 8, 4},
		{0, 10, 0, 7, 0, 0, 6},
		{0, 0, 5, 8, 0, 0, 1},
		{0, 0, 0, 4, 6, 1, 0},
	};	
		
	vertexNum = 7;
	capacity = vertexNum * vertexNum;
	bh = initBinaryHeap(capacity);
	temp = makeEmptyElement();
	
	printf("\n\n\t ====== test for kruskal alg building minimum spanning tree ======\n");
	//building binary heap with edge including 2 vertexs and its weight	
	for(i = 0; i < size; i++)
	{
	 	for(j = i+1; j < size; j++)	
			if(adjTable[i][j]) 
			{				
				temp->start = i;
				temp->end = j;
				temp->weight = adjTable[i][j];				
				insertHeap(temp, bh); // insertAdj the adjoining table over
			}
	}

	kruskal(bh, vertexNum);

	return 0;
} 

// allocate memory for the array with size
ElementTypePtr *makeEmptyArray(int size)
{
	ElementTypePtr *array;
	int i;

	array = (ElementTypePtr*)malloc(size * sizeof(ElementTypePtr)); 
	if(!array)
	{
		Error("out of space, from func makeEmptyArray");
		return NULL;
	}

	for(i=0; i<size; i++)	 
		array[i] = makeEmptyElement();	 

	return array;
}

// allocate memory for the single element 
ElementTypePtr makeEmptyElement()
{
	ElementTypePtr temp;

	temp = (ElementTypePtr)malloc(sizeof(ElementType));
	if(!temp)
	{
		Error("out of space, from func makeEmptyElement!");
		return NULL;
	}
	return temp;
}