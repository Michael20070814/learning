#include <stdio.h>
int main(void)
{
    int row, column;
    for (row = 1; row <= 5; row++)
    {    
        for (column = 1; column <= row; column++)
            printf("$");
        printf("\n");
    }
    return 0;
}