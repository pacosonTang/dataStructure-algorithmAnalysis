#include "open_addressing.h"
#include <math.h>

// checkout whether the value is prime number or not.
int isPrime(int value)
{
	int upper = (int)sqrt(value);
	int i;

	for(i=2; i<=upper; i++)
	{
		if(value%i == 0)
		{
			return 0;
		}
	}
	return 1;
}

// rehash.
HashTable rehash(HashTable oldTable)
{	
	int newSize = 2*oldTable->size, i;	
	HashTable newTable;	

	while(isPrime(++newSize)!=1);	
	newTable = initHashTable(newSize);
	// insertByLinearProbing
	for(i=0; i<oldTable->size; i++)
	{	
		if(oldTable->array[i]!=-1)
		{
			insertByLinearProbing(newTable, oldTable->array[i]);
		}
	}
	return newTable;
} 

int main()
{
	int values[] = {13, 15, 24, 6, 23};
	int size = 7, i;	
	HashTable table1 = initHashTable(size);
	
	// insertByLinearProbing
	for(i=0; i<5; i++)
	{
		insertByLinearProbing(table1, values[i]);
	}
	printf("insertByLinearProbing {13, 15, 24, 6, 23} into hashtable.\n");
	printHashTable(table1);

	// rehash	
	printf("\nafter rehash func executed \n");
	printHashTable(rehash(table1));
	freeHashTable(table1);
}
