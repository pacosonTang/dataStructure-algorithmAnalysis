#include<stdio.h>

/*打印整数的递归例程*/
void printout(unsigned int N);

main()
{    
    int temp = 1234554;
    printf("%d 可分解为 ",temp);    
    printout(temp);
    printf("\n");
}

void printout(unsigned int N)
{
    if(N >= 10)
        printout(N / 10);
    printf(" %d",N % 10);
}
