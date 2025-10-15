#include <stdio.h>
int main(void)
{
    long num;
    long sum = 0L;//保证以long形式储存更大的整数
    int status;

    printf("Please enter an integer to be summed (q to quit): ");
    status = scanf("%ld", &num);
    while (status == 1)
    {
        sum = sum + num;
        printf("Please enter next integer (q to quit): ");
        status = scanf("%ld", &num);
    }
    printf("Those integer sum to %ld.\n", sum);
    return 0;
}