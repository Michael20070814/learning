#include <stdio.h>
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
int main(void)
{
    int x = 1, y = 2;

    swap(&x, &y);
    printf("x: %d; y: %d", x, y);
    
    return 0;
}