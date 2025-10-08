#include <stdio.h>
int main(void)
{
    int ten = 10;
    int two = 2;

    printf("Doing it right:");
    printf("%d minus %d is %d\n", ten, two, ten-two);
    printf("Doing it wrong:");
    printf("%d minus %d is %d\n",ten);/*  不提供值时，会使用默认值，取决于内存位置  */
    return 0;
}