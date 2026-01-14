#include <stdio.h>
#include <stdbool.h>
int main(void)
{
    int row, column, n, m;
    scanf("%d%d", &row, &column);
    int game_board[row][column];
    for (int m = 0; m < row; m++)
    {
        for (int n = 0; n < column; n++)
        {
            scanf("%d", &game_board[m][n]);
        }
    }
    
    int continue_num = -1;
    int continue_value = 1;
    for (m = 0; m < row; m++)
    {
        for (n = 0; n < column; n++)
        {
            if (continue_num != game_board[m][n])
            {    
                continue_num = game_board[m][n];
                if (continue_value >= 3)
                {
                    for (int t = 1; t <= continue_value; t++)
                    {
                        // 要考虑列方向上是否会消除 但这里先不考虑
                        game_board[m][n - t] = 0;
                    }
                }
                continue_value = 1;
            }
            else
            {
                continue_value += 1;
            }
        }
        if (continue_value >= 3)
        {
            for (int t = 1; t <= continue_value; t++)
            {
                        // 要考虑列方向上是否会消除 但这里先不考虑
                game_board[m][n - t] = 0;
            }
        }
    }


    continue_value = 1;
    continue_num = -1;
    for (n = 0; n < column; n++)
    {
        continue_value = 1;
        continue_num = -1;
        for (m = 0; m < row; m++)
        {
            if (continue_num != game_board[m][n])
            {    
                continue_num = game_board[m][n];
                if (continue_value >= 3)
                {
                    for (int t = 1; t <= continue_value; t++)
                    {
                        // 前面考虑过列同时相消的情况这里不需要处理
                        game_board[m - t][n] = 0;
                    }
                }
                continue_value = 1;
            }
            else
            {
                continue_value += 1;
            }
        }
        if (continue_value >= 3)
        {
            for (int t = 1; t <= continue_value; t++)
            {
                // 要考虑行方向上是否会消除 但这里先不考虑
                game_board[m - t][n] = 0;
            }
        }  
    }


    for (int m = 0; m < row; m++)
    {
        for (int n = 0; n < column; n++)
        {
            printf("%d ", game_board[m][n]);
        }
        printf("\n");
    }

}