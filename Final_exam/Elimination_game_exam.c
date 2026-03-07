#include <stdio.h>
#include <stdbool.h>
int main(void)
{
    int row, column, n, m, index;
    index = 0;
    scanf("%d%d", &row, &column);
    int Elimination_x[row * column / 3];
    int Elimination_y[row * column / 3];
    int length[row * column / 3];
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
                    Elimination_x[index] = m;
                    Elimination_y[index] = n;
                    length[index] = continue_value;
                    index++;
                    // for (int t = 1; t <= continue_value; t++)
                    // {
                        
                    //     game_board[m][n - t] = 0;
                    // }
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
            Elimination_x[index] = m;
            Elimination_y[index] = n;
            length[index] = continue_value;
            index++;
            // for (int t = 1; t <= continue_value; t++)
            // {
            //     // 要考虑列方向上是否会消除 但这里先不考虑
            //     game_board[m][n - t] = 0;
            // }
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
    for (int x = 0; x < index; x++)
    {
        for (int t = 1; t <= length[x]; t++)
        {
            game_board[Elimination_x[x]][Elimination_y[x] - t] = 0; // 通过记忆第一次消除的位置，来达到行列同消
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