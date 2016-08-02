#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define ERROR(str) printf("error: %s", str)

typedef int HashNode;

struct HashTable;
typedef struct HashTable* HashTable;

struct HashTable
{
	int size;
	HashNode* array;
};

HashTable initHashTable(int size);
int hashFunc(ElementType value, int size);
int hashFunc2(ElementType value);
void insertByLinearProbing(HashTable table, ElementType value);
void insertBySquareProbing(HashTable table, ElementType value);
void insertByDoubleHash(HashTable table, ElementType value);
void printHashTable(HashTable ht);
int find(HashTable table, ElementType value);

// init hash table with size.
HashTable initHashTable(int size)
{
	HashTable table;	
	int i;

	// alloc memory for struct HashTable
	table = (HashTable)malloc(sizeof(struct HashTable));
	if(table==NULL)
	{
		ERROR("failed initHashTable() for there is no spare space.");
		return NULL;
	}
	table->size = size;

	// alloc memory for table->array.
	table->array = (HashNode*)malloc(sizeof(HashNode) * size);
	if(table->array==NULL)
	{
		ERROR("failed initHashTable() for there is no spare space.");
		return NULL;
	} 
	
	// give init values to every unit in table->array.
	for(i=0; i<size; i++)
	{
		table->array[i] = -1;
	}
	return table;
}

// hash function computing the pos that the value should be placed.
int hashFunc(ElementType value, int size)
{
	return value % size;
}

// the 2nd hash function.
int hashFunc2(ElementType value)
{
	int R = 7;
	return R - (value % R);
}

// find whether the node with value has been inserted into or not.
int find(HashTable table, ElementType value)
{
	int pos = hashFunc(value, table->size);
	HashNode temp = table->array[pos];
	
	return temp == value ? 1: 0;
}

// insert by linear probing.
void insertByLinearProbing(HashTable table, ElementType value)
{
	int pos;	
	int i;
	HashNode findNode = find(table, value);	
	
	if(findNode==0) // the value has not been inserted into hash table.
	{
		pos = hashFunc(value, table->size);
		i = 0;
		while(table->array[pos] != -1)
		{
			i++;
			pos = hashFunc(value+i, table->size);
		}
		table->array[pos] = value;
	}
	else
	{
		ERROR("failed insert() for the node with same value has been insert into the hashtable.");
	}
}

// insert by square probing.
void insertBySquareProbing(HashTable table, ElementType value)
{
	int pos;	
	int i;
	HashNode findNode = find(table, value);	
	
	if(findNode==0) // the value has not been inserted into hash table.
	{
		pos = hashFunc(value, table->size);
		i = 0;
		while(table->array[pos] != -1)
		{
			i++;
			pos = hashFunc(value+i*i, table->size);
		}
		table->array[pos] = value;
	}
	else
	{
		ERROR("failed insert() for the node with same value has been insert into the hashtable.");
	}
}

// insert by double hash which means there are 2 hash funcs.
void insertByDoubleHash(HashTable table, ElementType value)
{
	int pos;	
	int i;
	HashNode findNode = find(table, value);	
	
	if(findNode==0) // the value has not been inserted into hash table.
	{
		pos = hashFunc(value, table->size);
		i = 0;
		while(table->array[pos] != -1)
		{
			i++;
			pos += i * hashFunc2(value); // dont forget this line(highlight line).
			pos = hashFunc(pos, table->size);
		}
		table->array[pos] = value;
	}
	else
	{
		ERROR("failed insert() for the node with same value has been insert into the hashtable.");
	}
}

void printHashTable(HashTable ht)
{	
	int i;	
	
	if(ht==NULL)
	{
		ERROR("failed printHashTable(), for hashtable is NULL.");
		return ;
	}	
	for(i=0; i<ht->size; i++)
	{
		printf("\n\t hashtable->array[%d] = %d", i, ht->array[i]);		
	}
	printf("\n\n");
}