#include <stdio.h>
int Fibonacci1(int n);
int Fibonacci2(int n);
int main(void)
{
    int times = 0;
    printf("Please enter the circle times: ");
    scanf("%d", &times);
    printf("%d\n", Fibonacci1(times));
    printf("%d", Fibonacci2(times));
    return 0;
}
int Fibonacci1(int n)//recursion
{
    int n1 = 1;
    int n2 = 1;
    if (n == 1 || n == 2)
        return 1;
    else
    {
        return Fibonacci1(n - 1) + Fibonacci1(n - 2);
    }
}
int Fibonacci2(int n)//circle
{
    int result = 1;
    int x = 0;
    int y = 1;
    for (int count = 1; count <= n - 1; count++)
    {
        result = x + y;
        x = y;
        y = result;
    }
    return result;
}