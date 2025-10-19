#include <stdio.h>
int main(void)
{
    int row;
    char column;
    for (row = 1; row <= 6; row++)
    {    
        for (column = 'F'; column > 'F' - row; column--)
            printf("%c", column);
        printf("\n");
    }
    return 0;
}