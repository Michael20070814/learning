#include <stdio.h>
int main(void)
{
    long num;
    long sum = 0L;//保证以long形式储存更大的整数
    _Bool input_is_good;

    printf("Please enter an integer to be summed (q to quit): ");
    input_is_good = (scanf("%ld", &num));
    while (input_is_good = 1)
    {
        sum = sum + num;
        printf("Please enter next integer (q to quit): ");
        input_is_good = (scanf("%ld", &num));
    }
    printf("Those integer sum to %ld.\n", sum);
    return 0;
}