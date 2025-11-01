#include <stdio.h>
double return_max_minus_min(double ar[], int n);
int main(void)
{
    double list[10] = { 1.1, 2.6, 1.9, 12.3, 15.9, 21.4, 99.7, 0.9, 45.7, 16.8};
    printf("%lf", return_max_minus_min(list, 10));
    return 0;
}
double return_max_minus_min(double ar[], int n)
{
    double max, min;
    max = min = ar[0];
    for (int count = 0; count < n; count++)
    {
        if (ar[count] > max)
        {
            max = ar[count];
        }
        if (ar[count] < min)
            min = ar[count];
    }
    return max - min;
}