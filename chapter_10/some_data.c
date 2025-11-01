#include <stdio.h>
#define SIZE 4
int main(void)
{
    int some_data[SIZE] = {1492, 1066};
    int i;

    printf("%2s%14s\n", "i", "some_data[i]");
    for (int i = 0; i < SIZE; i++)
        printf("%2d%14d\n", i, some_data[i]);//数组中若有元素被初始化，其他未被初始化的元素自动赋值为0

    return 0;
}