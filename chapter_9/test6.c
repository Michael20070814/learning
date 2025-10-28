#include <stdio.h>
void sequence(double *x, double *y, double *z);
void swap(double *x, double *y);
int main(void)
{
    double x = 0;
    double y = 5;
    double z = -5;
    sequence(&x, &y, &z);
    printf("%lf %lf %lf", x , y, z);
}
void sequence(double *x, double *y, double *z)
{
    double temp;
    if (*x > *y)
    {
        if (*z > *x)
        {
            swap(z, x);
            swap(z, y);
        }
        else if (*z < *x && *z > *y)
        {
            swap(z, y);
        }
    }
    else
        if (*z > *y)
            swap(x, z);
        else if (*z < *y && *z > *x)
        {
            swap(x, y);
            swap(z, y);
        }
        else
            swap(x, y);
}
void swap(double *x, double *y)
{
    double temp;

    temp = *x;
    *x = *y;
    *y = temp;
}
