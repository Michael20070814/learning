#include <stdio.h>//计算任意数的幂
double power(double base, int pow);
int main(void)
{
    double base;
    int pow;
    scanf("%lf %d", &base, &pow);
    printf("%lf^%d = %lf", base, pow, power(base, pow));
    return 0;
}
double power(double base, int pow)
{
    double result = 1;
    if (base == 0)
        return 0;
    else if (pow == 0)
        return 1;
    else if (pow > 0)
    {
    for (int count = 1; count <= pow; count++)
        result *= base;
    }
    else
    {
        for (int count = 1; count <= -pow; count++)
        result *= base;
        result = 1 / result;
    }
    return result;
}