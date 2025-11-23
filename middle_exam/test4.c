#include <stdio.h>
int main(void)
{
    int num = 0;
    int temp;

    scanf("%d", &num);
    int input[num];
    int mark[10000];
    for (int n = 0; n < 10000; n++)
    {
        mark[n] = 0;
    }


    for (int n = 0; n < num; n++)
    {
        scanf("%d", &input[n]);
    }
    for (int n = 0; n < num; n++)
    {
        mark[input[n]] += 1;
    }
    for (int n = 0; n < 10000; n++)
    {
        if (mark[n] == 1)
            temp = n;
    }
    if (temp > 10000 || temp < -10000)
        temp = -2;
    printf("%d", temp);

    return 0;
}