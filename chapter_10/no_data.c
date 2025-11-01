#include <stdio.h>
#define SIZE 4
int main(void)
{
    int no_data[SIZE];

    printf("%2s%14s\n", "i", "no_data[i]");//单引号是字符常量
    for (int i = 0; i < SIZE; i++)
        printf("%2d%14d\n", i, no_data[i]);

    return 0;
}