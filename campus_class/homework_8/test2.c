#include <stdio.h>
void sequence(int *st, int size);
int main(void)
{
    int num1, num2, i = 0;
    scanf("%d", &num1);
    int list1[num1];
    for (int n = 0; n < num1; n++)
        scanf("%d", &list1[n]);
    scanf("%d", &num2);
    int list2[num2];
    for (int n = 0; n < num2; n++)
        scanf("%d", &list2[n]);
    int result[num1 + num2];
    for (int n = 0; n < num1; n++)
        result[n] = list1[n];
    for (int n = 0; n < num2; n++)
        result[n + num1] = list2[n];
    sequence(result, num1 + num2);
    i += num1 + num2 - 1;
    while (i >= 0)
    {
        if (i > 0 && result[i] == result[i-1])
            i = i - 2;
        else
        {
            printf("%d ", result[i]);
            i--;
        }
    }
    return 0;
}
void sequence(int *st, int size)
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