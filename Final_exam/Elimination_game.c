#include <stdio.h>
#include <stdbool.h>
int **input(int *row, int *column);
void row_eliminate(int row, int column, int input[row][column], int length, int x, int y);
void find_column_elimination(int row, int column, int input[row][column]);
void find_row_elimination(int row, int column, int **input);
void column_eliminate(int row, int column, int input[row][column], int length, int x, int y);
int main(void)
{
    int row, column;
    int **game_board = input(&row, &column);
    find_row_elimination(row, column, game_board);
}
int **input(int *row, int *column) // 检验正确
{
    scanf("%d%d", row, column);
    int game_board[*row][*column];
    for (int m = 0; m < *row; m++)
    {
        for (int n = 0; n < *column; n++)
        {
            scanf("%d", &game_board[m][n]);
        }
    }
    return game_board;
}
void find_row_elimination(int row, int column, int **input)
{
    int continue_num = -1;
    int continue_value = 0;
    for (int m = 0; m < row; m++)
    {
        for (int n = 0; n < column; n++)
        {
            if (continue_num != input[m][n])
            {    
                continue_num = input[m][n];
                if (continue_value >= 3)
                    row_eliminate(row, column, input, continue_value, m, n);
                continue_value = 0;
            }
            else
            {
                continue_value += 1;
            }
        }   
    }
}
void row_eliminate(int row, int column, int input[row][column], int length, int x, int y)
{
    for (int n = 1; n <= length; n++)
    {
        // 要考虑列方向上是否会消除 但这里先不考虑
        input[x][y - n] = 0;
    }
}
void find_column_elimination(int row, int column, int input[row][column])
{
    int continue_num = -1;
    int continue_value = 0;
    for (int n = 0; n < column; n++)
    {
        for (int m = 0; m < row; m++)
        {
            if (continue_num != input[m][n])
            {    
                continue_num = input[m][n];
                if (continue_value >= 3)
                    column_eliminate(row, column, input, continue_value, m, n);
                continue_value = 0;
            }
            else
            {
                continue_value += 1;
            }
        }   
    }
}
void column_eliminate(int row, int column, int input[row][column], int length, int x, int y)
{
    for (int n = 1; n <= length; n++)
    {
        // 要考虑行方向上是否会消除 但这里先不考虑
        input[x - n][y] = 0;
    }
}