#include <stdio.h>
double harmonic_mean(double x, double y);
int main()
{
    printf("%lf", harmonic_mean(10.2, 6.4));
    return 0;
}
double harmonic_mean(double x, double y)
{
    double temp1 = 1 / x;
    double temp2 = 1 / y;
    double result;
    result = (temp1 + temp2) / 2;
    return 1 / result;
}