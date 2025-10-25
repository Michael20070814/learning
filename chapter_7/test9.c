#include <stdio.h>//输入一个数，自动求出小于该数的所有素数
#include <stdbool.h>
int main(void)
{
    int input;
    bool isPrime = 1;
    printf("Please enter a positive integer: ");
    scanf("%d", &input);
    for (int i = 1; i <= input; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (i % j == 0 && j != 1 && j != i)
                isPrime *= 0;
            else
                isPrime *= 1;
        }
        if (isPrime == 1)
            printf("%d ", i);
        isPrime = 1;
    }
    return 0;
}