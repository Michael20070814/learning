#include <stdio.h>
#include "calc.h"
int main()
{
    int num, result;
    int i = 0;
    scanf("%d", &num);
    int list[num], goal[num];
    for (int n = 0; n < num; n++)
        scanf("%d", &list[n]);
    result = (int)LARGE(list, num, 3, 0);
    for (int n = 0; n < num; n++)
        if (list[n] == result)
        {
            goal[i] = n + 1;
            i++;
        }
    for (int j = 0; j < i; j++)
        printf("%d\n", goal[j]);
    
    return 0;
}