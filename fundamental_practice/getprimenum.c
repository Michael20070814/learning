#include <stdbool.h>
#include <stdio.h>

bool judge_prime(int input);
int revert_prime(int input);

int main(void)
{
    int input; 
    scanf("%d", &input);

    if (judge_prime(input) && judge_prime(revert_prime(input)))
        printf("yes\n");
    else
        printf("no\n");

    return 0;
}

bool judge_prime(int input)
{
    for (int m = 2; m * m <= input; m++)
    {
        if (input % m == 0)
            return false;
    }

    return true;
}

int revert_prime(int input)
{
    int result = 0;

    while (input >0)
    {
        result = result * 10 + input % 10;

        input /= 10;
    }

    return result;
}