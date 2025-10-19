#include <stdio.h>
int main(void)
{
    int row;
    int num = 0;
    char column;
    for (row = 1; row <= 6; row++)
    {   
        for (column = 'A' + num; column < 'A' + num + row; column++)
            printf("%c", column);
        printf("\n");
        num += row ;
    }
    return 0;
}