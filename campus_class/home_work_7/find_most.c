#include <stdio.h>
#define LEN 10000
int main(void)
{
    int times;
    int num[LEN], count[LEN];
    int order, temp;
    scanf("%d", &times);
    for (int n = 0; n < times; n++)
    {
        scanf("%d", &num[n]);
        count[n] = 1;
    }
    for (int n = 0; n < times; n++)
    {
        for (int j = 0; j < n; j++)
        {
            if (num[j] == num[n])
                count[j] += 1;
        }
    }
    temp = count[0];
    order = 0;
    for (int n = 0; n < times; n++)
    {
        if (count[n] > temp)
            order = n;
        temp = (temp > count[n]) ? temp : count[n];
    }
    printf("%d", num[order]);

    return 0;
}