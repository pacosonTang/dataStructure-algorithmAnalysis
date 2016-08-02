#include "separate_chaining.h"

int main()
{
	int values[] = {0, 1, 4, 25, 16, 9, 81, 64, 36, 49};
	int length = 10, i;	
	HashTable table = initHashTable(10);
	
	for(i=0; i<length; i++)
	{
		insert(table, values[i]);
	}
	printf("insert {0, 1, 4, 25, 16, 9, 81, 64, 36, 49} into hashtable.\n");
	printHashTable(table);
}