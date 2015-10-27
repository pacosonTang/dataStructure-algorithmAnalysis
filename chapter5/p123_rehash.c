#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define ElementType int
#define Error(str) printf("\n error: %s \n",str)   

struct HashTable;
typedef struct HashTable *HashTable;
struct HashEntry;
typedef struct HashEntry *HashEntry;
typedef HashEntry EntryArray;

HashTable initHashTable(int size);
int find(ElementType key, HashTable ht);
HashTable insert(ElementType key, HashTable ht);

enum EntryType {Legitimate, Empty, Deleted};

struct HashEntry
{
	ElementType key;
	enum EntryType status;
};

struct HashTable
{
	EntryArray entryArray;
	int capacity;
	int size;
};

//judge whether the value is prime or not, also 1  or 0
int isPrime(int value)
{
	int temp;
	int flag;

	flag = 1;
	temp = 2;
	while(temp < sqrt(value))
	{
		if(value % temp == 0)
			flag = 0;
		temp++;
	}
	return flag;
}

// compute the minial prime greater than the value
int nextPrime(int value)
{				
	value++;
	while(1)
	{
		if(isPrime(value))
			break;
		value++;
	}
	return value;
} 

// hash function
int hashFunc(int key, int capacity)
{
	return key % capacity;
}

// the rehash function to expand hash table capacity upto twice capcity
HashTable rehashFunc(HashTable ht)
{
	int capacity;
	int oldCapacity;
	int i;
	EntryArray temp;
		
	temp = ht->entryArray;
	oldCapacity = ht->capacity;
	capacity = nextPrime(ht->capacity * 2);
	ht = initHashTable(capacity);
	
	for(i = 0; i < oldCapacity; i++)
		if(temp[i].status == Legitimate)
			insert(temp[i].key, ht);
	free(temp);

	return ht;
}

// initializing HashTable with given size and the table size should be a prime number
HashTable initHashTable(int capacity)
{
	HashTable ht; 	
	int i;

	ht = (HashTable)malloc(sizeof(struct HashTable)); // allocate memory for HashTable
	if(!ht) 
	{
		Error("out of space, from func initHashTable");
		return NULL;
	}

	ht->capacity = capacity; // the table capacity should be a prime number
	ht->size = 0; // the number the hash table stores element
	ht->entryArray = (HashEntry)malloc(capacity * sizeof(struct HashEntry)); // allocate memory for entry array
	
	for(i = 0; i < capacity; i++) 
		ht->entryArray[i].status = Empty;
	return ht;
}

// insert the entry with value key into the Hash Table
HashTable insert(ElementType key, HashTable ht)
{
	int index;
	double loadFactor = 0.7; // let the load facotr equals to 0.7, of cource load factor depends on your mind
	double temp;

	index = find(key, ht);
	if(ht->entryArray[index].status != Legitimate)
	{
		ht->entryArray[index].status = Legitimate;
		ht->entryArray[index].key = key;
		ht->size++;
		// judge whether the load facotr is greater than the certain value
		temp = (double) ht->size / ht->capacity;		
		if(temp >= loadFactor)
			ht = rehashFunc(ht);
	}
	return ht;
}

// find the index the entry with key should be placed into 
int find(ElementType key, HashTable ht) // find the hash entry with value key 
{
	int index;	
	int collisionIndex;	
	int minus = -1;
	int temp;

	collisionIndex = 0;
	index = hashFunc(key, ht->capacity); // call the first hash function for allocating empty position for storing the key	
	temp = index;
	while(ht->entryArray[temp].status != Empty && ht->entryArray[temp].key != key ) // adopting square probing
	{
		if(minus == -1)
			collisionIndex++;
		minus *= -1;
		temp = collisionIndex * collisionIndex * minus;	 		
		temp = (index + temp) % ht->capacity;
	}		
	return temp;
}

void printHashTable(HashTable ht)
{
	ElementType key;
	int i;	
	
	if(!ht)
		Error("printing execution failure, for hashtable is null, from func printHashTable");	

	i = 0;
	while(i < ht->capacity)	
	{
		printf("\n\t index[%d] = ", i);
		key = ht->entryArray[i].key;	
		if(ht->entryArray[i].status == Legitimate)
			printf("%d", key);			
		else
			printf("NULL");
		printf("  ");		
		i++;
	}
	printf("\n\n");
}

int main()
{
	 
	HashTable ht = NULL;
	int dataSize = 4;
	int i;
	ElementType key[] = {13, 15, 24, 6};
	
	printf("\n\t=== test for rehashing the hash table with load factor 0.7 and capacity 7, and adopting square probing ===\n");
	ht = initHashTable(7);// the size of HashTable must be prime number;
	
	printf("\n\t=== test for inserting 13, 15, 24, 6 in turn into the hash table  ===\n");
	for(i = 0; i< dataSize; i++)	
 		ht = insert(key[i], ht);	
	printHashTable(ht);	  	

	printf("\n\t=== test for inserting 23 into the hash table  ===\n");
	ht = insert(23, ht);	
	printHashTable(ht);	  	

	printf("\n\t=== test for inserting 40 into the hash table  ===\n");
	ht = insert(40, ht);	
	printHashTable(ht);	  	

	return 0;
}