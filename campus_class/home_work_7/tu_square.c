#include <stdio.h>
#include <math.h>
#define LEN 15
double distance(int x1, int y1, int x2, int y2);
double tri_square(double length1, double length2, double length3);
double axis_square(int x1, int y1, int x2, int y2, int x3, int y3);
int main(void)
{
    int x[LEN], y[LEN];
    int time;
    double s[LEN - 2];
    double tot_square = 0;
    scanf("%d", &time);
    for (int num = 0; num < time; num++)
    {
        scanf("%d", &x[num]);
        scanf("%d", &y[num]);
    }
    for (int num = 0; num < time - 2; num++)
        s[num] = axis_square(x[0], y[0], x[num + 1], y[num + 1], x[num + 2], y[num + 2]);
    for (int num = 0; num < time - 2; num++)
        tot_square += s[num];
    printf("%.2lf", tot_square);

    return 0;
}
double distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
double tri_square(double length1, double length2, double length3)
{
    double square, p;
    p = (length1 + length2 + length3) / 2;
    square = sqrt(p * (p - length1) * (p - length2) * (p - length3));
    return square;
}
double axis_square(int x1, int y1, int x2, int y2, int x3, int y3)
{
    double distance1, distance2, distance3;
    distance1 = distance(x1, y1, x2, y2);
    distance2 = distance(x3, y3, x2, y2);
    distance3 = distance(x1, y1, x3, y3);
    return tri_square(distance1, distance2, distance3);
}
