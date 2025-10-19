#include <stdio.h>
int main(void)
{
    int int_up_limit, int_down_limit, num, sum;
    printf("Please enter a up_limit integer and a down_limit integer:(q to quit)");
    while ((scanf("%d %d", &int_up_limit, &int_down_limit)) == 2 && int_up_limit > int_down_limit)
    {
        for (num = int_down_limit, sum = 0; num <= int_up_limit; num++)
        {
            sum += num * num;
        }
        printf("The sums of the squares from %d to %d is %d\n", int_down_limit * int_down_limit,
                int_up_limit * int_up_limit, sum);
        printf("Please enter a up_limit integer and a down_limit integer:(q to quit)");
    }
    printf("Done!\n");
    return 0;
}