#include <stdio.h>
#include <stdlib.h>
int ** get_co_matrix(int n, int i, int **matrix);
int get_determinant(int n, int **matrix);
void free_matrix(int **matrix, int n);
int main(void)
{
    int row1, column1;
    printf("Please enter the matrix's number of row and column\n");
    scanf("%d%d", &row1, &column1);
    if (row1 != column1)
    {    
        printf("Enter error!");
        return 0;
    }
    printf("Now enter the matrix, row by row.\n");
    int **matrix = (int **)malloc(column1 * sizeof(int *));
    for (int i = 0; i < column1; i++)
        matrix[i] = (int *)malloc(column1 * sizeof(int));
    for (int i = 0; i < row1; i++)
        for (int j = 0; j < column1; j++)
            scanf("%d", &matrix[i][j]);
    int result = get_determinant(column1, matrix);
    printf("The determinant is %d\n", result);

    return 0;
}
int ** get_co_matrix(int n, int i, int **matrix)
{
    int m = 0;
    int **matrix1 = (int **)malloc((n - 1) * sizeof(int *));
    for (int p = 0; p < n - 1; p++)
        matrix1[p] = (int *)malloc((n - 1) * sizeof(int));
    for (int p = 1; p < n; p++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {    
                matrix1[p - 1][m] = matrix[p][j];
                m++;
            }
        }
        m = 0;
    }
    return matrix1;
}
int get_determinant(int n, int **matrix)
{
    int result = 0;
    if (n == 1)
        return matrix[0][0];
    else
        for (int i = 0; i < n; i++)
        {   
            int **matrix1 = get_co_matrix(n, i, matrix);
            result += get_determinant(n - 1, matrix1) * matrix[0][i] * (i % 2 == 0 ? 1 : -1);
            free_matrix(matrix1, n - 1);
        }
    return result;
}
void free_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}