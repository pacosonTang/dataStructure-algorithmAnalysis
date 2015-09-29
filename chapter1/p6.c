#include<stdio.h>

/* 满足F(0)=0 且 F(X)=2F(X-1)+X^2 */

int F(int);

int main()
{    
    for(int i = 0; i <= 10; i++)
        printf("F(%d) = %-4d\n",i,F(i));         
}

int F(int x)
{
    if(x == 0)
        return 0;
    else 
		return 2 * F(x - 1) + x * x;
}
