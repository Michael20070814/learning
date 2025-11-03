#include <stdio.h>
void enter_list(double (*ptr)[5], int n, int n1);
double return_row_average(double *ptr, int n1);
double cal_all_aver(int n, int n2, double ar[n][n2]);
double find_max(double ar[][5], int n, int n1);
void output_outcome(double aver[], double all_aver, double max);
int main(void)
{
    double list[3][5] = {};
    double list1[3] = {};
    double average = 0;
    double max = 0;
    enter_list(list, 3, 5);
    for (int n = 0; n < 3; n++)
    {
        list1[n] = return_row_average(list[n], 5);
    }
    average = cal_all_aver(3, 5, list);
    max = find_max(list, 3, 5);
    output_outcome(list1, average, max);
}
void enter_list(double (*ptr)[5], int n, int n1)
{
    double temp;
    printf("Please enter 3 * 5 number: ");
    for (int row = 0; row < n; row++)
    {
        for (int column = 0; column < n1; column++)
        {
            scanf("%lf", &temp);
            *(*(ptr + row) + column) = temp;
        }
    }
}
double return_row_average(double *ptr, int n1)
{
    double result = 0;
    for (int column = 0; column < n1; column++)
        result += *(ptr + column);
    return result / 5;
}
double cal_all_aver(int n, int n2, double ar[n][n2])//展示二维数组
{
    double result = 0;
    for (int count = 0; count < n; count++)
    {
        for (int count1 = 0; count1 < n2; count1++)
            result += ar[count][count1];
    }
    return result / (n * n2);
}
double find_max(double ar[][5], int n, int n1)
{
    double max = ar[0][0];
    for (int count = 0; count < n; count++)
    {
        for (int count1 = 0; count1 < n1; count1++)
        {
            if (max < ar[count][count1])
                max = ar[count][count1];
        }
    }
    return max;
}
void output_outcome(double aver[], double all_aver, double max)
{
    for (int n = 0; n < 3; n++)
    {
        printf("%lf\n", aver[n]);
    }
    printf("%lf\n", all_aver);
    printf("%lf\n", max);
}