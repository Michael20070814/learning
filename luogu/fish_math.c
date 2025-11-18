#include <stdio.h>
int main(void)
{
    int number[100];
    int temp;
    int num = 0;

    while (scanf("%d", &temp) == 1 && temp != 0)
    {
        number[num] = temp;
        num++;
    }
    for (int n = num - 1; n >= 0; n--)
        printf("%d ", number[n]);

    return 0;
}