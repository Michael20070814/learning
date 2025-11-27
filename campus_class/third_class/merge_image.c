#include <stdio.h>
#define ROW 5
#define I_COL 5
int main(void)
{
    char H[ROW][I_COL] = {
        {'H',' ', ' ', ' ', 'H'},
        {'H',' ', ' ', ' ', 'H'},
        {'H', 'H', 'H', 'H', 'H'},
        {'H',' ', ' ', ' ', 'H'},
        {'H',' ', ' ', ' ', 'H'},
    };
    char I[ROW][I_COL] = {
        {' ','I', 'I', 'I', ' '},
        {' ',' ', 'I', ' ', ' '},
        {' ', ' ', 'I', ' ', ' '},
        {' ',' ', 'I', ' ', ' '},
        {' ','I', 'I', 'I', ' '},
    };
    FILE *fp;
    fp = fopen("test2.txt", "w");
    for (int row = 0; row < ROW; row++)
    {
        char hp = H[row];
        char ip = I[row];
        for (int col = 0; col < I_COL; col++)
            fprintf(fp, "%c", *(hp + col));
        fprintf(fp, "\n");
        for (int col = 0; col < I_COL; col++)
            fprintf(fp, "%c", *(ip + col));
    }
}