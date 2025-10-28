#include <stdio.h>
void sequence(double *x, double *y, double *z);
void swap(double *x, double *y);
int main(void)
{
    double x = 1000;
    double y = 6546;
    double z = 1200;
    sequence(&x, &y, &z);
    printf("%lf %lf %lf", x , y, z);
    return 0;
}
void sequence(double *x, double *y, double *z)
{
    double temp;
    if (*x < *y)
        swap(x, y);
    if (*y < *z)
        swap(y, z);
    if (*x < *y)
        swap(x, y);
}
void swap(double *x, double *y)
{
    double temp;

    temp = *x;
    *x = *y;
    *y = temp;
}
