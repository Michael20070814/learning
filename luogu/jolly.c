#include <stdio.h>
int main(void)
{
    int num, record;
    int value = 1;
    record = 0;

    scanf("%d", &num);
    int jolly[num];
    for (int n = 0; n < num; n++)
        scanf("%d", &jolly[n]);
    for (int n = 1; n < num; n++)
    {
        for (int i = 0; i < num - 1; i++)
        {   
            if (jolly[i + 1] - jolly[i] < 0)
                if (jolly[i+1] - jolly[i] == -n)
                    value *= 0;
                else
                    ;
            else//想让这个else匹配外层的if必须加上花括号才可以，否则加一个没有用的else
                if (jolly[i+1] - jolly[i] == n)
                    value *= 0;
        }
        if (value == 0)
            record += 1;
        value = 1;
    }
    if (record == num - 1)
        printf("Jolly");
    else
        printf("Not jolly");

    return 0;
}