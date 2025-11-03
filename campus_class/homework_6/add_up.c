#include <stdio.h>
int sum_up(int n);
int main(void)
{
    int sum, times;
    sum = 0;
    scanf("%d", &times);
    for (int i = 1; i <= times; i++)
        sum += sum_up(i);
    printf("%d", sum);
}
int sum_up(int n)
{
    return (n + 1) * n / 2;
}