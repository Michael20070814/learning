#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int **matrix_input(int *size);
int **matrix_add(int **matrix1, int **matrix2, int size);
int **matrix_sub(int **matrix1, int **matrix2, int size);
void print(int **result, int size);

int main(void)
{
    char ch;
    int size = 0;
    int **result = matrix_input(&size);

    while (isspace(ch = getchar()))
            continue;

    while (ch != '#')
    {
        getchar(); // eat the space

        int **matrix2 = matrix_input(&size);

        if (ch == '+')
            result = matrix_add(result, matrix2, size);
        else
            result = matrix_sub(result, matrix2, size);
        
        
        free(matrix2);

        while (isspace(ch = getchar()))
            continue;
    }

    print(result, size);
    free(result);

    return 0;
}

int **matrix_input(int *size)
{
    if (*size == 0)
    {
        int n;
        scanf("%d", &n);
        *size = n;
    }

    int **matrix = (int **) malloc(*size * sizeof(int *));

    for (int i = 0; i < *size; i++)
        matrix[i] = (int *) malloc(*size * sizeof(int));

    for (int i = 0; i < *size; i++)
        for (int j = 0; j < *size; j++)
            scanf("%d", &matrix[i][j]);

    return matrix;
}

int **matrix_add(int **matrix1, int **matrix2, int size)
{
    int **matrix = (int **) malloc(size * sizeof(int *));

    for (int i = 0; i < size; i++)
        matrix[i] = (int *) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = matrix1[i][j] + matrix2[i][j];

    return matrix;
}
int **matrix_sub(int **matrix1, int **matrix2, int size)
{
    int **matrix = (int **) malloc(size * sizeof(int *));

    for (int i = 0; i < size; i++)
        matrix[i] = (int *) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = matrix1[i][j] - matrix2[i][j];

    return matrix;
}
void print(int **result, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%5d", result[i][j]);
        printf("\n");
    }
}