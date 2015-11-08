#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str) 

struct UnionSet;
typedef struct UnionSet* UnionSet;

// we adopt the child-sibling expr
struct UnionSet
{
	int parent;
	int size;
	ElementType value;
};

UnionSet makeEmpty(); 
UnionSet* initUnionSet(int size, ElementType* data);
void printSet(UnionSet* set, int size);
void printArray(ElementType data[], int size);
int find(int index, UnionSet* set);
void pathCompress(int, UnionSet*);

// initialize the union set 
UnionSet* initUnionSet(int size, ElementType* data)
{
	UnionSet* set;	
	int i;

	set = (UnionSet*)malloc(size * sizeof(UnionSet));
	if(!set)
	{
		Error("out of space, from func initUnionSet");        
        return NULL;
	}	

	for(i=0; i<size; i++)
	{
		set[i] = makeEmpty();
		if(!set[i])
			return NULL;
		set[i]->value = data[i];
	}
	
	return set;
}

// allocate the memory for the single UnionSet and evaluate the parent and size -1
UnionSet makeEmpty()
{
	UnionSet temp;

	temp = (UnionSet)malloc(sizeof(struct UnionSet));
	if(!temp)
	{
		Error("out of space, from func makeEmpty!");        
		return NULL;
	}

	temp->parent = -1;
	temp->size = 1;
	return temp;
}


// merge set1 and set2 by size
void setUnion(UnionSet* set, int index1, int index2)
{
	//judge whether the index1 or index2 equals to -1 ,also -1 represents the root
	if(index1 != -1)
		index1 = find(index1, set);
	if(index2 != -1)
		index2 = find(index2, set);

	if(set[index1]->size > set[index2]->size)
	{
		set[index2]->parent = index1;
		set[index1]->size += set[index2]->size;
	}
	else
	{
		set[index1]->parent = index2;
		set[index2]->size += set[index1]->size;
	}
} 

//find the root of one set whose value equals to given value
int find(int index, UnionSet* set) 
{
	UnionSet temp;	
	
	while(1)
	{
		temp = set[index];
		if(temp->parent == -1)
			break;
		index = temp->parent;
	}

	return index;		
}	

// conducting path compression towards union set with given index
void pathCompress(int index, UnionSet* set)
{	
	int root;
	int i;
	int parent;

	//1st step: find the top root contains the element under index	
	root = find(index, set);

	//2nd step: path compression begins
	i = set[index]->parent;
	set[index]->parent = root;
	while(i != -1) 
	{		
		parent = set[i]->parent;				
		if(parent == root)
			break;
		set[i]->parent = root;
		i = parent;
	}
}

int main()
{
	int size;
	UnionSet* unionSet;
	ElementType data[] = {110, 245, 895, 658, 321, 852, 147, 458, 469, 159, 347, 28};

	size = 12;
	printf("\n\t====== test for conducting path compression towards union set by size ======\n");
	//printf("\n\t=== the initial array is as follows ===\n");
	//printArray(data, depth); 
	
	printf("\n\t=== the init union set are as follows ===\n");
	unionSet = initUnionSet(size, data); // initialize the union set over
	//printSet(unionSet, size);
	
	printf("\n\t=== after union(0, 1) + union(2, 3) + union(4, 5) + union(6, 7) + union(8, 9) + union(10 ,11) ===\n");
	setUnion(unionSet, 0, 1);
	setUnion(unionSet, 2, 3);
	setUnion(unionSet, 4, 5);
	setUnion(unionSet, 6, 7);
	setUnion(unionSet, 8, 9);	
	setUnion(unionSet, 10, 11);	
	//printSet(unionSet, size);

	printf("\n\t=== after union(1, 3) + union(5, 7) + union(9, 11) ===\n");
	setUnion(unionSet, 1, 3);
	setUnion(unionSet, 5, 7);
	setUnion(unionSet, 9, 11);
	//printSet(unionSet, size);  
	
	printf("\n\t=== after union(3, 7) + union(7, 11) ===\n");
	setUnion(unionSet, 3, 7);
	setUnion(unionSet, 7, 11);	
	printSet(unionSet, size); 
	
	printf("\n\t=== after pathCompress(0, unionSet) + pathCompress(8, unionSet) ===\n");
	pathCompress(0, unionSet) ;
	pathCompress(8, unionSet);
	printSet(unionSet, size); 

	return 0;
}

void printArray(ElementType data[], int size)
{
	int i;

	for(i = 0; i < size; i++)	 
		printf("\n\t data[%d] = %d", i, data[i]);					 
	printf("\n\n");
} 

void printSet(UnionSet* set, int size)
{
	int i;
	UnionSet temp;
	
	for(i = 0; i < size; i++)
	{		
		temp = set[i];
		printf("\n\t parent[%d] = %d", i, temp->parent);				
	}
	printf("\n");
}
