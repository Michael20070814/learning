#include <stdio.h>
int main(void)
{
    int count, sum, day;//声明
    count = 0;
    sum = 0;/* 表达式语句 */
    printf("Please enter the day you like:\n");
    scanf("%d", &day);
    while (count++ < day)/* 迭代语句 */
    {
        sum = sum + count;
    }
    printf("sum = %d\n", sum);

    return 0;/* 跳转语句 */
}