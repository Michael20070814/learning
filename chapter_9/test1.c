#include <stdio.h>
double min(double x, double y);
int main()
{
    printf("%lf", min(23, 29));
    return 0;
}
double min(double x, double y)
{
    return (x > y) ? y : x;
}