#include <stdio.h>
int main(void)
{
    int x, y, z;
    float average;
    scanf("%d%d%d", &x, &y, &z);
    printf("%d\n", x+ y + z);
    average = (float)(x + y + z) / 3;
    printf("%.2f\n", average);
}