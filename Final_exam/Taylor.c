#include <stdio.h>
#include <math.h>
double jiecheng(int n);
double Taylor_expansion(double x, double a, int n);
double multichoice(double a, int n);
int main(void)
{
    double result = 0;
    double x, a;
    int n;
    double gap, temp;
    temp = 0;
    scanf("%lf%lf%d", &x, &a, &n);
    for (int num = 0; num < n + 1; num++)
        result += Taylor_expansion(x, a, num);
    for (int num = 0; num < n; num++)
        temp += Taylor_expansion(x, a, num);
    gap = result - temp;
    if (gap < 0)
        gap = -gap;
    printf("%.9lf %.9lf", result, gap);
}
double jiecheng(int n)
{
    if (n == 1 || n == 0)
        return 1.0;
    else
        return jiecheng(n - 1) * n;
}
double Taylor_expansion(double x, double a, int n)
{
    return multichoice(a, n) * pow(x, n) / jiecheng(n);
}
double multichoice(double a, int n)
{
    double result = 1.0;
    if (n == 0)
        return 1;
    for (int num = 0; num < n; num++)
    {
        result = result * (a - num);
    }
    return result;
}