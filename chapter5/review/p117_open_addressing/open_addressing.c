#include "open_addressing.h"

int main()
{
	int values[] = {89, 18, 49, 58, 69};
	int length = 10, i;	
	HashTable table1 = initHashTable(length);
	HashTable table2 = initHashTable(length);
	HashTable table3 = initHashTable(length);
	
	// insertByLinearProbing
	for(i=0; i<5; i++)
	{
		insertByLinearProbing(table1, values[i]);
	}
	printf("insertByLinearProbing {89, 18, 49, 58, 69} into hashtable.\n");
	printHashTable(table1);

	// insertBySquareProbing
	for(i=0; i<5; i++)
	{
		insertBySquareProbing(table2, values[i]);
	}
	printf("insertBySquareProbing {89, 18, 49, 58, 69} into hashtable.\n");
	printHashTable(table2);

	// insertByDoubleHash
	for(i=0; i<5; i++)
	{
		insertByDoubleHash(table3, values[i]);
	}
	printf("insertByDoubleHash {89, 18, 49, 58, 69} into hashtable.\n");
	printHashTable(table3);
}