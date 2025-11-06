#include <stdio.h>
void enter_list(int n, int n1, double (*ptr)[n1]);
double return_row_average(double *ptr, int n1);
double cal_all_aver(int n, int n2, double ar[n][n2]);
double find_max(double ar[][5], int n, int n1);
void output_outcome(double aver[], double all_aver, double max, int rows);
int main(void)
{
    int row, column;
    double average = 0;
    double max = 0;
    printf("Please enter the rows and the columns: ");
    scanf("%d%d", &row, &column);
    double list[row][column];
    double list1[row];
    
    enter_list(row, column, list);
    for (int n = 0; n < row; n++)
    {
        list1[n] = return_row_average(list[n], column);
    }
    average = cal_all_aver(row, column, list);
    max = find_max(list, row, column);
    output_outcome(list1, average, max, row);
}
void enter_list(int n, int n1, double (*ptr)[n1])
{
    double temp;
    printf("Please enter %d * %d number: ", n, n1);
    for (int row = 0; row < n; row++)
    {
        for (int column1 = 0; column1 < n1; column1++)
        {
            scanf("%lf", &temp);
            *(*(ptr + row) + column1) = temp;
        }
    }
}
double return_row_average(double *ptr, int n1)
{
    double result = 0;
    for (int column2 = 0; column2 < n1; column2++)
        result += *(ptr + column2);
    return result / n1;
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
void output_outcome(double aver[], double all_aver, double max, int rows)
{
    for (int n = 0; n < rows; n++)
    {
        printf("%lf\n", aver[n]);
    }
    printf("%lf\n", all_aver);
    printf("%lf\n", max);
}