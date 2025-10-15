#include <stdio.h>
int main(void)
{
    int count, sum, num;//声明
    count = 0;
    sum = 0;/* 表达式语句 */
    printf("Please enter the num you like:\n");
    scanf("%d", &num);
    while (count++ < num)/* 迭代语句 */
    {
        sum = sum + count * count;
    }
    printf("sum = %d\n", sum);

    return 0;/* 跳转语句 */
}