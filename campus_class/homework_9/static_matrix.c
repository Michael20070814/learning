#include <stdio.h>
#include <string.h>
#include "calc.h"

struct Str
{
    int number;
    int times;
};
void sequence(struct Str ar[], int length);
void swap(struct Str *a, struct Str *b);
int main(void)
{
    struct Str group[9] = {0};
    int value, i, j = 0;
    int row, column;
    FILE *fp = fopen("data.ext", "r");
    fscanf(fp, "%d%d", &row, &column);
    int matrix[row][column];
    for (int row1 = 0; row1 < row; row1++)
        for (int column1; column1 < column; column1++)
            fscanf(fp, "%d", &matrix[row1][column1]);
    for (int row1 = 0; row1 < row; row1++)
    {
        for (int column1 = 0; column1 < column; column1++)
        {    
            value = 1;
            for (i = 0; i < 9; i++)
            {    
                if (group[i].number == matrix[row1][column1])
                {    
                    value *= 0;
                    break;
                }
            }
            if (value == 0)
                group[i].times += 1;
            else
            {
                group[j].number = matrix[row1][column1];
                group[j].times = 1;
                j++;
            }
        }
    }
    sequence(group, j);
    printf("%d", group[0].number);
}
void sequence(struct Str ar[], int length)
{
    for (int num = 0; num < length; num++)
        for (int q = 0; q < length; q++)
            if (q< length - 1 && ar[q].times < ar[q + 1].times)
                swap(&ar[q], &ar[q + 1]);
}
void swap(struct Str *a, struct Str *b)
{
    struct Str temp = *a;
    *a = *b;
    *b = temp;
}