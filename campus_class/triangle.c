#include <stdio.h>
int main(void)
{
    for (int count = 1; count <= 9; count++)
    {
        for (int i = 1; i <= count; i++)
            printf("%d", count);
        printf("\n");
    }
    return 0;
}