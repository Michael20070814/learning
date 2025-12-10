#include <stdio.h>
int main(void)
{
    int row1, column1, row2, column2;
    int x_coordinate, y_coordinate;
    scanf("%d%d", &row1, &column1);
    int matrix1[row1][column1];
    for (int i = 0; i < row1; i++)
        for (int j = 0; j < column1; j++)
            scanf("%d", &matrix1[i][j]);
    scanf("%d%d", &row2, &column2);
    int matrix2[row2][column2];
    for (int i = 0; i < row2; i++)
        for (int j = 0; j < column2; j++)
            scanf("%d", &matrix2[i][j]);
    scanf("%d%d", &x_coordinate, &y_coordinate);
    if (y_coordinate + column2 - 1 <= column1 && x_coordinate + row2 - 1 <= row1)
    {
        for (int i = 0; i < row2; i++)
            for (int j = 0; j < column2; j++)
                matrix1[x_coordinate + i - 1][y_coordinate + j - 1] = matrix2[i][j];
    }
    else
    {
        for (int i = 0; i < row2 && x_coordinate + i <= row1; i++)
            for (int j = 0; j < column2 && y_coordinate + j <= column1; j++)
                matrix1[x_coordinate + i - 1][y_coordinate + j - 1] = matrix2[i][j];
    }

    for (int i = 0; i < row1; i++)
    {    
        for (int j = 0; j < column1; j++)
            printf("%d ", matrix1[i][j]);
        printf("\n");
    }
    return 0;
}