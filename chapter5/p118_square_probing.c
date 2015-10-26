#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct HashTable;
typedef struct HashTable *HashTable;
struct HashEntry;
typedef struct HashEntry *HashEntry;
typedef HashEntry EntryArray;

HashTable initHashTable(int size);
int find(ElementType key, HashTable ht);
void insert(ElementType key, HashTable ht);

enum EntryType {Legitimate, Empty, Deleted};

struct HashEntry
{
	ElementType key;
	enum EntryType status;
};

struct HashTable
{
	EntryArray entryArray;
	int size;
};

// hash function
int hashFunc(int key, int size)
{
	return key % size;
}

// initializing HashTable with given size and the table size should be a prime number
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
	ht->entryArray = (HashEntry)malloc(size * sizeof(struct HashEntry)); // allocate memory for entry array
	
	for(i = 0; i < size; i++) 
		ht->entryArray[i].status = Empty;
	return ht;
}

// insert the entry with value key into the Hash Table
void insert(ElementType key, HashTable ht)
{
	int index;

	index = find(key, ht);
	if(ht->entryArray[index].status != Legitimate)
	{
		ht->entryArray[index].status = Legitimate;
		ht->entryArray[index].key = key;
	}
}

// find the index the entry with key should be placed into 
int find(ElementType key, HashTable ht) // find the hash entry with value key 
{
	int index;
	int collisionIndex;	
	int minus = -1;
	int temp;

	collisionIndex = 0;
	index = hashFunc(key, ht->size);
	while(ht->entryArray[index].status != Empty && ht->entryArray[index].key != key ) // adopting square probing
	{
		if(minus == -1)
			collisionIndex++;
		minus *= -1;
		temp = collisionIndex * collisionIndex * minus;	// 

		index +=  temp;		
		index  %= ht->size;
	}		

	return index;
}

void printHashTable(HashTable ht)
{
	ElementType key;
	int i;	
	
	if(!ht)
		Error("printing execution failure, for hashtable is null, from func printHashTable");
	printf("\n\t=== separate linked list in hash table are as follows ===\n");

	i = 0;
	while(i < ht->size)	
	{
		printf("\n\t index[%d] = ", i);
		key = ht->entryArray[i++].key;							
		printf("%d", key);			
		printf("  ");		
	}
	printf("\n\n");
}

int main()
{
	HashTable ht = NULL;
	int dataSize = 5;
	int i;
	ElementType key[] = {89, 18, 49, 58, 69};

	ht = initHashTable(10);// the size of HashTable must be prime number;
	
	for(i = 0; i< dataSize; i++)	
		insert(key[i], ht);	

	printHashTable(ht);	 

	return 0;
}