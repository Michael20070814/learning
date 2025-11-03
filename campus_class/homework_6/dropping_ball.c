#include <stdio.h>
#define ratio 0.25
float power(float base, int power);
int main(void)
{
    int m, n;
    float total_distance, height;
    scanf("%d%d", &n, &m);
    height = power(ratio, m);
    total_distance = (8.0 / 3) * n * (1 - height) - n;
    printf("%.2f\n", total_distance);
    printf("%.2f", height * n);
}
float power(float base, int power)
{
    float result = 1;
    for (int n = 0; n < power; n++) 
        result = base * result;
    return result;
}