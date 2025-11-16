#include <stdio.h>
int num[100000] = {};
int input[10000];
int main(void)
{
    num[0] = 1;
    num[1] = 3;
    int found = 1;
    int order;
    order = 2;
    int i = 0;
    while (scanf("%d", &input[i]) != EOF && i < 10000)
        i++;
    for (int n = 0; n < 10000 && order < 100000; n++)
    {
        for (int i = 0; i < n && order < 100000; i++)
        {
            num[order] = (i + 2) * (n + 2) - 2;
            order++;
        }
    }
    for (int j = 0; j < i; j++)
    {    for (int n = 0; n < 100000; n++)
        {
            if (input[j] == num[n])
            {
                printf("Yes\n");
                found = 0;
                break;
            }
        }
        if (found)
        printf("No\n");
        found = 1;
    }
    return 0;

}
