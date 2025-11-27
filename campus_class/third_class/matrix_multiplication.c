#include <stdio.h>
int main()
{
    int A[4][6] = {{1, 1, 1, 1, 1, 1}, {2, 2, 2, 2, 2, 2}, {3, 3, 3, 3, 3, 3}, {4, 4, 4, 4, 4, 4}};
    int B[6][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    int C[4][3] = {};

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            for (int n = 0; n < 6; n++)
                C[i][j] += A[i][n] * B[n][j];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {    
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}