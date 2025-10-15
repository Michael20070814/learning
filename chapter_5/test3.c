#include <stdio.h>
#define DAY_PER_WEEK 7
int main(void)
{
    int day;
    int week;
    int remain_day;
    printf("please enter the day:\n");
    scanf("%d", &day);
    while (day > 0)
    {
        week = day / DAY_PER_WEEK;
        remain_day = day % DAY_PER_WEEK;
        printf("%d days are %d weeks, %d days.\n", day, week, remain_day);
        printf("please enter the day:\n");
        scanf("%d", &day);
    }
    return 0;
}