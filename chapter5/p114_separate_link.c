#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct LinkedNode;
typedef struct LinkedNode *LinkedNode;
typedef LinkedNode *LinkedList;
struct HashTable;
typedef struct HashTable *HashTable;

HashTable initHashTable(int size);
//void destoryTable();
LinkedNode find(ElementType key, HashTable ht);
void insert(ElementType key, HashTable ht);
//ElementType retrieve(Position p);

struct LinkedNode
{
	ElementType key;
	LinkedNode next;
};

struct HashTable
{
	LinkedList linkedList;
	int size;
};

// hash function
int hashFunc(int key, int size)
{
	return key % size;
}

// initializing HashTable with given size 
HashTable initHashTable(int size)
{
	HashTable ht; 	
	int i;

	ht = (HashTable)malloc(sizeof(struct HashTable)); // allocate memory for HashTable
	if(!ht) 
	{
		Error("out of space, from func initHashTable");
		return NULL;
	}

	ht->size = size; // the table size should be a prime number
	ht->linkedList = (LinkedList)malloc(size * sizeof(struct LinkedNode)); // allocate memory for Separate Linked List
	if(!ht->linkedList) 
	{
		Error("out of space, from func initHashTable");
		return NULL;  
	}
	
	for(i = 0; i< size; i++) // allocate memory for head node of Separate Linked List
	{
		ht->linkedList[i] = (LinkedNode)malloc(sizeof(struct LinkedNode));
		if(!ht->linkedList[i]) 
			Error("out of space, from func initHashTable");				
		else
			ht->linkedList[i]->next = NULL;
	}
	return ht;
}

void insert(ElementType key, HashTable ht)
{		
	LinkedNode temp;
	LinkedNode node;
	LinkedNode tempTwo;
	

	temp = find(key, ht); // find the position for inserting key into the linked list, for both inserting and finding have the same search path for searching the node with key
	if(!temp) {
		node = (LinkedNode)malloc(sizeof(struct LinkedNode)); // allocate memory to node with key
		if(!node) 
		{
			Error("insertion failure, for out of space, from func insert");
			return ;
		}
		else
		{
			node->key = key;
			node->next = NULL; // building the linked node with value key and pointer next over
			
			temp = ht->linkedList[hashFunc(key, ht->size)];
			tempTwo = temp->next;
			temp->next = node;
			node->next = tempTwo;			
		}				
	}
	else
		Error("insertion failure, for there already has the node with key , from func insert");
}

LinkedNode find(ElementType key, HashTable ht) // find the linkednode with value key in HashTable's LinkedList 
{
	int index;
	LinkedNode temp;

	index = hashFunc(key, ht->size);
	temp = ht->linkedList[index];	
	temp = temp->next; // now temp points to the first node in the link responding to index not head node 
	while(temp && temp->key != key)
		temp = temp->next;
	
	return temp;
}

void printHashTable(HashTable ht)
{
	int key;
	int i;
	LinkedNode temp;

	key = -1;
	if(!ht)
		Error("printing execution failure, for hashtable is null, from func printHashTable");
	printf("\n\t=== separate linked list in hash table are as follows ===\n");
	for(i = 0;i<ht->size; i++)
	{
		printf("\n\t index[%d] = ", i);
		temp = ht->linkedList[i]->next;
		while(temp)
		{			
			printf("%d", temp->key);
			temp = temp->next;
			printf("  ");
		}
	}
	printf("\n\n");
}

int main()
{
	HashTable ht = NULL;
	int dataSize = 10;
	int i;
	ElementType key[] = {1, 0, 81, 4, 64, 25, 16, 36, 9, 49};

	ht = initHashTable(10);
	for(i = 0;i< dataSize; i++)
		insert(key[i], ht);
	printHashTable(ht);	

	return 0;
}