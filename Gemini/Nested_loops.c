#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int *find_max_row(int row, int column, int input[row][column]); // 二维数组的传参
bool verify_min_column(int row,int column, int row_index, int column_index, int input[row][column]);
int main(void)
{
    int row, column;
    int flag = 0;
    scanf("%d%d", &row, &column);
    int arr[row][column];
    for (int m = 0; m < row; m++)
        for (int n = 0; n < column; n++)
            scanf("%d", &arr[m][n]); // 数据的读取
    int *max_row = find_max_row(row, column, arr);
    for (int m = 0; m < row; m++)
    {
        if (verify_min_column(row,column,  m, max_row[m], arr))
        {    
            printf("%d at (%d, %d)", arr[m][max_row[m]], m, max_row[m]); // 打印鞍点
            flag += 1;
        }
    }
    if (flag == 0)
        printf("No Saddle Point");
    
    free(max_row);

    return 0;
}
int *find_max_row(int row, int column, int input[row][column]) // 找出每一行最大元素所在的列标
{
    int *row_max = (int *)malloc(sizeof(int) * row);
    for (int j = 0; j < row; j++)
    {
        int max = input[j][0];
        int index = 0;
        for (int i = 0; i < column; i++)
        {
            if (input[j][i] > max)
            {    
                max = input[j][i]; // 考虑到一行中有两个最大值的情况，最好不要分开，在一起解决这个问题
                index = i;
            }
        }
        row_max[j] = index;
    }
    return row_max;
}
bool verify_min_column(int row, int column,  int row_index, int column_index, int input[row][column]) // 判断当前行的最大值是否是列的最小值
{
    bool flag = true;
    for (int i = 0; i < row; i++)
        if (input[i][column_index] < input[row_index][column_index])
            flag = false;
    if (flag)
        return true;
    else
        return false;
}