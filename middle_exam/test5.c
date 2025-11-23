#include <stdio.h>
int continue_add(int s, int *input);
int main(void)
{
    int n, targetsum;
    scanf("%d", &n);
    int value = 1;
    int a = 0;

    int input[n];
    for (int num = 0; num < n; num++)
        scanf("%d", &input[num]);
    scanf("%d", &targetsum);
    if (n > 15)
        a = 1;
    else if (n > 7)
        a = 2;
    else if (n > 3)
        a = 3;
    else if (n > 1)
        a = 4;
    switch(a)
    {
        case 1:
        for (int s = 15; s < 31 && s < n; s++)
        {
            if (input[s] == -1)
                continue;
            if (continue_add(s, input) == targetsum)
            {    
                value *= 0;
                break;
            }
        }
        break;
        case 2:
        for (int s = 7; s < 15 && s < n; s++)
        {
            if (input[s] == -1)
                continue;
            if (continue_add(s, input) == targetsum)
            {    
                value *= 0;
                break;
            }
        }
        break;
        case 3:
        for (int s = 3; s < n && s < 7; s++)
        {
            if (input[s] == -1)
                continue;
            if (continue_add(s, input) == targetsum)
            {    
                value *= 0;
                break;
            }
        }
        break;
        case 4:
        for (int s = 1; s < n && s < 3; s++)
        {
            if (input[s] == -1)
                continue;
            if (continue_add(s, input) == targetsum)
            {    
                value *= 0;
                break;
            }
        }
        break;
        default:
        if (input[0] == targetsum)
            value *= 1;
    }
    if (value == 0)
        printf("1");
    else
        printf("0");
    
    return 0;
}
int continue_add(int s, int *input)
{
    int result = 0;

    if (s > 0)
    {
        result += continue_add((s+1) / 2 - 1, input) + input[s];
    }
    else
        result += input[0];
    return result;
}