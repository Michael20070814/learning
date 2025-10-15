#include <stdio.h>
#define TEN 103
int main(void)
{
    int n = 96;

    while (n++ < TEN)
        printf("%5c", n);
    printf("\n");
    return 0;
}