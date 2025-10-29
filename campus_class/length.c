#include <stdio.h>
#include <math.h>
double length(int x1, int y1, int x2, int y2);
double square(double l1, double l2, double l3);
int main(void)
{
    double x1, y1, x2, y2, x3, y3;
    double len1, len2, len3;

    printf("Please enter six numbers: ");
    scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
    len1 = length(x1, y1, x2, y2);
    len2 = length(x3, y3, x2, y2);
    len3 = length(x1, y1, x3, y3);

    printf("Length:%f \n", len1);
    printf("Square: %lf", square(len1, len2, len3));
    return 0;
}
double length(int x1, int y1, int x2, int y2)
{
    int dx, dy;
    double len;

    dx = x1 - x2;
    dy = y1 - y2;

    len = sqrt(dx*dx + dy * dy);

    return len;
}
double square(double l1, double l2, double l3)
{
    double p = (l1 + l2 + l3)/2;

    return sqrt(p * (p - l1) * (p - l2) * (p - l3));
}