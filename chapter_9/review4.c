#include <stdio.h>
int sum(int m, int n)
{
    return m + n;
}
int alter(int *x, int *y)
{
    int temp1, temp2;

    temp1 = *x;
    temp2 = *y;

    *x = temp1 - temp2;
    *y = temp1 + temp2;
}
void salami(int num)
{
    int count;
    for (count = 1; count <= num; count++)
        printf(" O salami mio!\n");
}
int maximum(int x, int y, int z)
{
    int biggest;
    biggest = (x > y) ? x : y;
    biggest = (biggest > z) ? biggest : z;
    return biggest;
}
int main(void)
{
    int x = 10;
    int y = 5;

    alter(&x, &y);
    printf("x is %d, and y is %d", x, y);
    salami(x);
    printf("%d", maximum(31,29,26));

    return 0;
}