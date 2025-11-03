#include <stdio.h>
void copy_arr(double ar[], const double ar1[], int n);
int main(void)
{
    int num = 3;
    const double list[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    double list_2[num];
    copy_arr(list_2, &list[2], num);
}
void copy_arr(double ar[], const double *ptr, int n)
{
    for (int count = 0; count < n; count++)
    {
            ar[count] = *(ptr + count);
    }
    for (int count = 0; count < n; count++)
            printf("%.2lf ", ar[count]);//展示一维数组
    printf("\n");
}