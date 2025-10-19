#include <stdio.h>
int main(void)
{
    int number[8], index;
    for (index = 0; index <= 7; index++)
    {
        printf("Please enter a integer: ");
        scanf("%d", &number[index]);
    }
    for (index = 7; index >= 0; index--)
    {
        printf("%d", number[index]);
    }
    return 0;
}