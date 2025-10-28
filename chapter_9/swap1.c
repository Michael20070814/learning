#include <stdio.h>
void intercharge(int * u, int * v);

int main(void)
{
    int x = 5, y = 10;

    printf("Originally x = %d and y = %d.\n", x, y);
    intercharge(&x, &y);
    printf("Now x = %d and y = %d.\n", x, y);

    return 0;
}
void intercharge(int * u, int * v)
{
    int temp; 

    temp = *u;
    *u = *v;
    *v = temp;//没有把值返回给主调函数
}