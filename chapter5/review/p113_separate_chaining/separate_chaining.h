#include <stdio.h>
#include <malloc.h>

#define ElementType int
#define ERROR(str) printf("error: %s", str)

struct HashNode;
typedef struct HashNode* HashNode;

struct HashTable;
typedef struct HashTable* HashTable;

struct HashNode
{
	ElementType value;
	HashNode next;
};

struct HashTable
{
	int size;
	HashNode* linkedList;
};

HashTable initHashTable(int size);
HashNode createHashNode(ElementType value);
int hashFunc(ElementType value, int size);
void insert(HashTable table, ElementType value);
void printHashTable(HashTable ht);
HashNode find(HashTable table, ElementType value);

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

	// alloc memory for table->table.
	table->linkedList = (HashNode*)malloc(sizeof(HashNode) * size);
	if(table->linkedList==NULL)
	{
		ERROR("failed initHashTable() for there is no spare space.");
		return NULL;
	}

	// alloc memory for every HashNode in table->linkedList.
	for(i=0; i<size; i++)
	{
		table->linkedList[i] = (HashNode)malloc(sizeof(struct HashNode));
		if(table->linkedList[i]==NULL)
		{
			ERROR("failed initHashTable() for there is no spare space.");
			return NULL;
		}
		table->linkedList[i]->next = NULL;
	}

	return table;
}

// create hash node with value.
HashNode createHashNode(ElementType value)
{
	HashNode temp;

	temp = (HashNode)malloc(sizeof(struct HashNode));
	if(temp==NULL)
	{
		ERROR("failed createHashNode() for there is no spare space.");
		return NULL;
	}
	temp->value = value;
	temp->next = NULL;
	return temp;
}

int hashFunc(ElementType value, int size)
{
	return value % size;
}

HashNode find(HashTable table, ElementType value)
{
	int pos = hashFunc(value, table->size);
	HashNode temp = table->linkedList[pos];
	
	temp = temp->next; // now temp points to the first node in the link responding to index not linkedList node 
	while(temp && temp->value != value) // highlight line.
	{
		temp = temp->next; 
	}
	return temp;
}

void insert(HashTable table, ElementType value)
{
	int pos;	
	HashNode findNode = find(table, value);
	HashNode temp;
	
	if(findNode==NULL)
	{
		pos = hashFunc(value, table->size);
		temp = table->linkedList[pos];
		while(temp->next)
		{
			temp = temp->next;
		}
		temp->next = createHashNode(value);		
	}
	else
	{
		ERROR("failed insert() for the node with same value has been insert into the hashtable.");
	}
}

void printHashTable(HashTable ht)
{
	int key;
	int i;
	HashNode temp;

	key = -1;
	if(!ht)
	{
		ERROR("failed printHashTable(), for hashtable is null.");
		return ;
	}	
	for(i=0;i<ht->size; i++)
	{
		printf("\n\t index[%d] = ", i);
		temp = ht->linkedList[i]->next;
		while(temp != NULL)
		{			
			printf("%d", temp->value);
			temp = temp->next;
			printf("  ");
		}
	}
	printf("\n\n");
}