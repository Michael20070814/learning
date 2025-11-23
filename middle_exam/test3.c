#include <stdio.h>
double trimmed_mean(double arr[], int n, int k);
void BUBBLE_SORT(double arr[], int n);
int main(void)
{
    int n, k;
    double result = 0;

    scanf("%d%d", &n, &k);
    double input[n];
    for (int num = 0; num < n; num++)
    {
        scanf("%lf", &input[num]);
    }
    BUBBLE_SORT(input, n);
    result = trimmed_mean(input, n, k);
    printf("%.2lf", result);

    return 0;
}
double trimmed_mean(double arr[], int n, int k)
{
    double result = 0;

    for (int num = k; num < n - k; num++)
    {
        result += arr[num];
    }

    return result / (n - 2 * k);
}
void BUBBLE_SORT(double arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}