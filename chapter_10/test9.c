#include <stdio.h>
void copy_arr(int n, int n2, double ar[n][n2], const double ar1[n][n2])//拷贝二维数组
{
    for (int count = 0; count < n; count++)
        for (int count1 = 0; count1 < n2; count1++)
            ar[count][count1] = ar1[count][count1];
}
void show_arr(int n, int n2, double ar[n][n2])//展示二维数组
{
    for (int count = 0; count < n; count++)
    {
        for (int count1 = 0; count1 < n2; count1++)
            printf("%.2lf ", ar[count][count1]);
        printf("\n");
    }
}
int main(void)
{
    const double list[3][5] = {{1.1, 2.2, 3.3, 4.4, 5.5}, {6.6, 7.7, 8.8, 9.9, 10.1},
                        {11.2, 12.3, 13.4, 14.5, 15.6}};
    double list_2[3][5];
    copy_arr(3, 5, list_2, list);
    show_arr(3, 5, list_2);
}