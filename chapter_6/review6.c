#include <stdio.h>
int main(void)
{
    int i, j;
    for (i = 0; i <= 3; i += 1)
    {
        for (j = 0; j <= 7; j += 1)
            printf("$");
        printf("\n");
    }
    return 0;
}