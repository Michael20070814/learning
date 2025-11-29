#include <stdio.h>
#include <string.h>
int main()
{
    int row1, column1, row2, column2;
    printf("This is a program for computing the matrix multipication:\n");
    while (1)
    {
        printf("Please enter first matrix's number of row and column\n");
        scanf("%d%d", &row1, &column1);
        printf("Now enter the matrix, row by row.\n");
        int matrix1[row1][column1];
        for (int i = 0; i < row1; i++)
            for (int j = 0; j < column1; j++)
                scanf("%d", &matrix1[i][j]);
        printf("Please enter second matrix's number of row and column\n");
        scanf("%d%d", &row2, &column2);

        if (column1 != row2)
        {    
            printf("Your two matrix mutiplication is invalid.Please enter again:");
            continue;
        }

        printf("Now enter the matrix, row by row.\n");
        int matrix2[row2][column2];
        for (int i = 0; i < row2; i++)
            for (int j = 0; j < column2; j++)
                scanf("%d", &matrix2[i][j]);
        int result[row1][column2];
        memset(result, 0, sizeof result);
        for (int i = 0; i < row1; i++)
            for (int j = 0; j < column2; j++)
                for (int a = 0; a < column1; a++)
                    result[i][j] += matrix1[i][a] * matrix2[a][j];
        printf("The results are as follows\n");
        for (int i = 0; i < row1; i++)
        {    
            for (int j = 0; j < column2; j++)
                printf("%d ", result[i][j]);
            printf("\n");
        }
        break;
    }
    
    return 0;
}