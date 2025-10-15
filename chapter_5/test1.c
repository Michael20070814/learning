#include <stdio.h>
#define MIN_PER_HOUR 60
int main(void)
{
    int min;
    int hour;
    int remain_min;
    printf("please enter the time:\n");
    scanf("%d", &min);
    while (min > 0)
    {
        hour = min / MIN_PER_HOUR;
        remain_min = min % MIN_PER_HOUR;
        printf("The time is %d hour and %d minute\n", hour, remain_min);
        printf("please enter the time:\n");
        scanf("%d", &min);
    }
    return 0;
}