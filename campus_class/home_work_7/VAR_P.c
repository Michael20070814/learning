#include <stdio.h>
#define LEN 1000
double VAR_P(double arr[], int n);
double square(double num);
int main(void)
{
    double ch[LEN] = {};
    double temp;
    int num;

    //printf("Please enter the number of the num you want to enter: ");
    scanf("%d", &num);
    //printf("Please enter %d numbers: ", num);
    for (int n = 0; n < num; n++)
    {
        scanf("%lf", &temp);
        ch[n] = temp;
    }
    printf("%lf", VAR_P(ch, num));
}
double square(double num)
{
    return num * num;
}
double VAR_P(double arr[], int n)
{
    double average;
    double temp = 0;
    for (int num = 0; num < n; num++)
        temp += arr[num];
    average = temp / n;
    temp = 0;
    for (int num = 0; num < n; num++)
        temp += square(arr[num] - average);
    return temp / n;
}