#include <stdio.h>
#include <ctype.h>
int Hide_num_sum(char *input);
int main(void)
{
    char buffer[100];
    fgets(buffer, 99, stdin);
    int result = Hide_num_sum(buffer);
    printf("%d", result);
    getchar();

    return 0;
}
int Hide_num_sum(char *input)
{
    int result = 0;
    int num, num_flag;
    num = 0;
    num_flag = 0;
    char *p = &input[0];
    while (*p != '\0')
    {
        // 简化后的核心逻辑
        if (isdigit(*p)) {
        // 只要是数字，就一直累积，不用管 flag
            num = num * 10 + (*p - '0');
            num_flag = 1; // 标记但我手里有货
        } else {
            // 遇到非数字，如果有货（flag为1），就结算
            if (num_flag == 1) {
                result += num;
                num = 0;
                num_flag = 0;
            }
        }
        p++;
    }
    if (num != 0)
        result += num;
    return result;
}