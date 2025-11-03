#include <stdio.h>
void show_arr(int n, int n2, int ar[n][n2])//展示二维数组
{
    for (int count = 0; count < n; count++)
    {
        for (int count1 = 0; count1 < n2; count1++)
            printf("%d ", ar[count][count1]);
        printf("\n");
    }
}
void double_arr(int n, int n2, int ar[n][n2])
{
    for (int count = 0; count < n; count++)
    {
        for (int count1 = 0; count1 < n2; count1++)
            ar[count][count1] *= 2;
    }
}
int main(void)
{
    int list[3][5] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}};
    show_arr(3, 5, list);
    double_arr(3, 5, list);
    show_arr(3, 5, list);
    return 0;
}