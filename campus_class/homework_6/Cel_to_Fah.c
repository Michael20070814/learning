#include <stdio.h>
#define FAH 32
int main(void)
{
    int celsius;
    float Fah;
    scanf("%d", &celsius);
    Fah = (float)celsius * 9 / 5 + FAH;
    printf("%.1f", Fah);
    return 0;
}