#include <stdio.h>
#include "calc.h"
int main(void)
{
    int row, column;
    FILE *fp = fopen("data.txt", "r");
    fscanf(fp, "%d %d", &row, &column);
    double data[row * column];
    for (int i = 0; i < row * column; i++)
        fscanf(fp, "%lf", &data[i]);
    int goal = (int) MODE_SNGL(data, row * column);
    printf("%d\n", goal);
    fclose(fp);

    return 0;
}