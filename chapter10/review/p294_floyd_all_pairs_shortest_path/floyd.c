#include <stdio.h>
#include <limits.h>

#define ElementNum 4
#define MyMax 100000
void printArray(int array[ElementNum][ElementNum]);

// 弗洛伊德算法用于 计算所有点对最短路径.
// distance 是邻接矩阵， 而 path 是中转点.
void floyd_all_pairs(int distance[ElementNum][ElementNum], int path[ElementNum][ElementNum])
{
	int i, j, k;

	for(k=0; k<ElementNum; k++)
	{
		for(i=0; i<ElementNum; i++)
		{
			for(j=0; j<ElementNum; j++)
			{
				if(distance[i][j] > distance[i][k] + distance[k][j])
				{
					distance[i][j] = distance[i][k] + distance[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}

int main()
{
	// 邻接矩阵
	int distance[ElementNum][ElementNum] = 
	{
		{0, 5, MyMax, 7},
		{MyMax, 0, 4, 2},
		{3, 3, 0, 2},
		{MyMax, MyMax, 1, 0},
	};
	int path[ElementNum][ElementNum] = 
	{
		{-1, -1, -1, -1},
		{-1, -1, -1, -1},
		{-1, -1, -1, -1},
		{-1, -1, -1, -1},
	};
	// 弗洛伊德算法用于 计算所有点对最短路径.
	floyd_all_pairs(distance, path);
	
	// 打印 floyd 的 计算结果.
	printf("\n\t === distance array are as follows.===\n");
	printArray(distance);

	printf("\n\t === path array are as follows.===\n");
	printArray(path);	
}

void printArray(int array[ElementNum][ElementNum])
{
	int i, j;

	for(i=0; i<ElementNum; i++)
	{
		for(j=0; j<ElementNum; j++)
		{
			printf("%3d, ", array[i][j]);
		}
		printf("\n");
	}
}