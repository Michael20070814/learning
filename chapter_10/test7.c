#include <stdio.h>
void copy_arr(double ar[][3], const double ar1[][3], int n, int n2);
int main(void)
{
    double list_2[2][3] = {{ 1.2, 2.7, 3.9 }, { 9.8, 4.6, 7.9 }};
    double list_1[2][3];
    copy_arr(list_1, list_2, 2, 3);
    return 0;
}
void copy_arr(double ar[][3], const double ar1[][3], int n, int n2)
{
    for (int count = 0; count < n; count++)
    {
        for (int count1 = 0; count1 < n2; count1++)
            ar[count][count1] = ar1[count][count1];
    }
    for (int count = 0; count < n; count++)
        for (int count1 = 0; count1 < n2; count1++)
            printf("%.2lf ", ar[count][count1]);
    printf("\n");
}