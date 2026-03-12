#include <stdio.h>

int decompose(int input, int *num);

int main(void)
{
    int input;int num;
    scanf("%d", &input);

    int fundament = decompose(input, &num);

    if (fundament != -1)
    {
        printf("%d=", input);
        for (int index = 0; index < num; index++)
        {
            printf("%d", fundament + index);
            if (index != num - 1)
                printf("+");
        }
    }
    else
        printf("No Answer");
    return 0;
}

int decompose(int input, int *num)
{
    int temp; int result;int index;

    for (index = 1; index < input; index++)
    {
        result = 0;
        for (temp = index; result < input; temp++)
        {
            result += temp;
            if (result == input)
                break;
        }
        if (result == input)
            break;
    }
    if (result == input)
    {
        *num = temp - index + 1;
        return index;
    }
    else
        return -1;
}