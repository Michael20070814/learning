#include <stdio.h>
#include <math.h>
float cal_square(float a, float b, float c);
int main(void)
{
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    printf("%.3f", cal_square(x, y, z));
}
float cal_square(float a, float b, float c)
{
    float result = 0;
    float p;
    p = (a + b + c) / 2;
    result = sqrt(p*(p - a)*(p - b)*(p - c));
    return result;
}