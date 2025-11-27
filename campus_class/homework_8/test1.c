#include <stdio.h>
void sequence(double *st, int size);
int main()
{
    int num, i;
    scanf("%d", &num);
    double list[num];
    for (int n = 0; n < num; n++)
        scanf("%lf", &list[n]);
    scanf("%d", &i);
    sequence(list, num);
    switch (i)
    {
        case 0:
            printf("%.2lf", list[0]);
            break;
        case 1:
            if ((num - 1) % 4 == 0)
                printf("%.2lf", list[(num - 1) / 4]);
            else
                printf("%.2lf", list[(num - 1)/4] * ((num - 1) / 4 + 1 - (num - 1) * 0.25) + list[(num - 1)/4 + 1] * ((num - 1) * 0.25 - (num - 1) / 4));
            break;
        case 2:
            if ((num - 1) % 2 == 0)
                printf("%.2lf", list[(num - 1) / 2]);
            else
                printf("%.2lf", list[(num - 1)/2] * ((num - 1) * 0.5 + (num - 1) / 2) + list[(num - 1)/2 + 1] * ((num - 1) / 2 + 1 - (num - 1) * 0.5));
            break;
        case 3:
            if ((num - 1) % 4 == 0)
                printf("%.2lf", list[(num - 1) / 4]);
            else
                printf("%.2lf", list[(num - 1)/4 * 3] * ((num - 1) * 3 / 4 + 1 - (num - 1) * 0.25 * 3) + list[(num - 1)/4 * 3+ 1] * ((num - 1) * 0.25 * 3- (num - 1) * 3 / 4));
            break;
        case 4:
            printf("%.2lf", list[num - 1]);
            break;
    }
    return 0;
}
void sequence(double *st, int size)
{
    double temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (st[j] > st[j + 1])
            {
                temp = st[j];
                st[j] = st[j + 1];
                st[j + 1] = temp;
            }
        }
    }
}