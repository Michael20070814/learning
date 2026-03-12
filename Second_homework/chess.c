#include <stdio.h>
#include <stdlib.h>
#define SIZE 19
int **input(void);
int judge_row(int *arr[SIZE], int *x, int *y);
int judge_column(int *arr[SIZE], int *x, int *y);
int judge_left_slope(int *arr[SIZE], int *x, int *y);
int judge_right_slope(int *arr[SIZE], int *x, int *y);

int main(void)
{
    int **arr = input();
    int x = 0; int y = 0; int color = -1;

    if ((color = judge_row(arr, &x, &y)) > 0)
         printf("%d:%d,%d\n", color, x, y);
    else if ((color = judge_column(arr, &x, &y)) > 0)
        printf("%d:%d,%d\n", color, x, y);
    else if ((color = judge_left_slope(arr, &x, &y)) > 0)
        printf("%d:%d,%d\n", color, x, y);
    else if ((color = judge_right_slope(arr, &x, &y)) > 0)
        printf("%d:%d,%d\n", color, x, y);
    else
        printf("No\n");

    free(arr);

    return 0;
}

int **input(void)
{
    // 分配行指针数组
    int **matrix = (int **)malloc(sizeof(int *) * SIZE);
    if (matrix == NULL)
    {
        perror("malloc");
        return NULL;
    }

    // 为每一行分配空间
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * SIZE);
        if (matrix[i] == NULL)
        {
            perror("malloc");
            // 释放已分配的行
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &matrix[i][j]);

    return matrix;
}
int judge_row(int *arr[SIZE], int *x, int *y)
{
    int i; int j;
    int flag = 0;
    int num = 0;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (arr[i][j] == 1 && flag == 0)
            {
                flag = 1;
                num++;
            }
            else if (arr[i][j] == 2 && flag == 0)
            {
                flag = 2;
                num++;
            }
            else if (arr[i][j] == 1 && flag == 1)
                num++;
            else if (arr[i][j] == 2 && flag == 2)
                num++;
            else if (arr[i][j] == 1 && flag == 2)
            {
                num = 1;
                flag = 1;
            }
            else if (arr[i][j] == 2 && flag == 1)
            {
                num = 1;
                flag = 2;
            }
            else
            {
                flag = 0;
                num = 0;
            }

            if (num == 4)
                break;
        }
        if (num == 4)
            break;
        num = 0;
        flag = 0;
    }

    if ((i < SIZE && j + 1 < SIZE && arr[i][j + 1] == 0) || (i < SIZE && j - num >= 0 && arr[i][j - num] == 0))
    {
        *y = i + 1;
        *x = j - num + 2;
        return flag;
    }
    else
        return -1;
}
int judge_column(int *arr[SIZE], int *x, int *y)
{
    int i; int j;
    int flag = 0;
    int num = 0;
    for (j = 0; j < SIZE; j++)
    {
        for (i = 0; i < SIZE; i++)
        {
            if (arr[i][j] == 1 && flag == 0)
            {
                flag = 1;
                num++;
            }
            else if (arr[i][j] == 2 && flag == 0)
            {
                flag = 2;
                num++;
            }
            else if (arr[i][j] == 1 && flag == 1)
                num++;
            else if (arr[i][j] == 2 && flag == 2)
                num++;
            else if (arr[i][j] == 1 && flag == 2)
            {
                num = 1;
                flag = 1;
            }
            else if (arr[i][j] == 2 && flag == 1)
            {
                num = 1;
                flag = 2;
            }
            else
            {
                flag = 0;
                num = 0;
            }

            if (num == 4)
                break;
        }
        if (num == 4)
            break;
        num = 0;
        flag = 0;
    }

    if ((j < SIZE && i + 1 < SIZE && arr[i + 1][j] == 0) || (j < SIZE && i - num >= 0 && arr[i - num][j] == 0))
    {    
        *x = i - num + 2;
        *y = j + 1;
        return flag;
    }
    else
        return -1;
}
int judge_left_slope(int *arr[SIZE], int *x, int *y)
{
    int i; int j;
    int flag = 0; int num = 0;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (arr[i][j] == 0)
                continue;
            int temp = 0; num = 0;
            flag = arr[i][j];
            while (temp < 4)
            {   
                if (i + temp < SIZE && j + temp < SIZE && arr[i + temp][j + temp] == flag)
                    num++;
                else
                    break;
                temp++;
            }

            if (num == 4)
                break;
        }
        if (num == 4)
            break;
    }

    if ( num == 4 && ((i - 1 >= 0 && j - 1 >= 0 && arr[i - 1][j - 1] == 0) || (i + num < SIZE && j + num < SIZE && arr[i + num][j + num] == 0)))
    {
        *y = i + 1;
        *x = j + 1;
        return flag;
    }
    else
        return -1;
}

int judge_right_slope(int *arr[SIZE], int *x, int *y)
{
    int i; int j;
    int flag = 0; int num = 0;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (arr[i][j] == 0)
                continue;
            int temp = 0; num = 0;
            flag = arr[i][j];
            while (temp < 4)
            {   
                if (i + temp < SIZE && j - temp >= 0 && arr[i + temp][j - temp] == flag)
                    num++;
                else
                    break;
                temp++;
            }

            if (num == 4)
                break;
        }
        if (num == 4)
            break;
    }

    if (num == 4 && ((i - 1 >= 0 && j + 1 < SIZE && arr[i + 1][j - 1] == 0) || (i + num < SIZE && j - num >= 0 && arr[i + num][j - num] == 0)))
    {
        *y = j + 1;
        *x = i + 1;
        return flag;
    }
    else
        return -1;
}