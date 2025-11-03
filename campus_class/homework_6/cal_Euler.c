#include <stdio.h>
double factorial(int n);
double cal_Euler(double m, int n);
double power(double base, int exp);
int main(void)
{
    int n;
    double x;
    scanf("%lf%d", &x, &n);
    printf("%lf", cal_Euler(x, n));
}
double factorial(int n)
{
    double result = 1;
    for (int count = 1; count <= n; count++)
        result *= count;
    return result;
}
double cal_Euler(double m, int n)
{
    double result = 0;
    for (int count = 0; count <= n; count++)
        result += power(m, count) / factorial(count);
    return result;
}
double power(double base, int exp)
{
    double result = 1.0;
    for (int n = 0; n < exp; n++) 
        result = base * result;
    return result;
}