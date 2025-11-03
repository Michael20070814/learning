#include <stdio.h>
double factorial(int n)
{
    double result = 1;
    int count = 0;
    while (count++ < n)
        result *= count;
    return result;
}
double power(double base, int exp)
{
    double result = 1.0;
    for (int n = 0; n < exp; n++) 
        result = base * result;
    return result;
}
double cal_cos(double m, int n)
{
    double result = 0;
    for (int count = 0; count <= 2 * n; count = count + 2)
        result += power(m, count) / factorial(count) * power(-1, count / 2);
    return result;
}
int main(void)
{
    double x;
    int n;
    scanf("%lf%d", &x, &n);
    printf("%.8lf", cal_cos(x, n));
}