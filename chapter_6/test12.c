#include <stdio.h>
int power(int m, int n);
int main(void)
{
    int times;
    float start, sum;
    printf("I'm a calculator of (1+ 1/2 +1/3 +....)\n");
    printf("Please enter the number of terms you want to me to calculate:");
    scanf("%d", &times);
    for (start = 1; start <= times; start++)
    {
        sum += 1.0 / start;
    }
    printf("The sums of it is %f\n", sum);
    sum = 0;
    printf("I'm a calculator of (1 - 1/2 + 1/3 -....)\n");
    printf("Please enter the number of terms you want to me to calculate:");
    scanf("%d", &times);
    for (start = 1; start <= times; start++)
    {
        sum += 1.0 / start * (float)power(-1, (int)start - 1);
    }
    printf("The sums of it is %f\n", sum);
    printf("Done!\n");
    return 0;
}
int power(int m, int n)
{
    int result, i;
    result = 1;
    for (i = 1; i <= n; i++)
        result *= m;
    return result;
}