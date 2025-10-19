#include <stdio.h>
int main(void)
{
    double str1[8];
    double str2[8];
    int num;

    for (num = 0; num <= 7; num++)
    {
        printf("Please enter a float:");
        scanf("%lf", &str1[num]);
    }
    num = 0;
    str1[0] = str1[0];
    for (num = 1; num <= 7; num++)
    {
        str2[num] = str1[num] + str2[num - 1];
    }
    for (num = 0; num <= 7; num++)
    {
        printf("%.2lf ", str1[num]);
    }
    printf("\n");
    for (num = 0; num <= 7; num++)
    {
        printf("%.2lf ", str2[num]);
    }
}