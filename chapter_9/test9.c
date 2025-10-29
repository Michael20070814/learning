#include <stdio.h>//使用递归计算指数
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
    double multiply = (pow > 0) ? base : 1 / base;
    if (base == 0)
        return 0;
    else if (pow == 0 )
        return 1;
    else
        result = multiply * power(base, (pow > 0) ? pow - 1 : pow + 1);
    return result;
}