#include <stdio.h>
int main(void)
{
    int d1, d2, d3;
    int max;
    scanf("%d%d%d", &d1, &d2, &d3);
    max = d1;
    if (max < d2)
        max = d2;
    if (max <d3)
        max = d3;
    printf("Max: %d", max);

    return 0;
}