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
    num_flag = 0;
    char *p = &input[0];
    while (*p != '\0')
    {
        if (!isdigit(*p))
        {    
            if (num_flag == 1)
            {
                result += num;
                num = 0;
            }
            num_flag = 0;
            p++;
        }
        else
        {
            if (num_flag == 0)
            {
                num = *p - '0'; // 一定要注意数据类型，这里的*p是char类型，不能直接赋值
                num_flag = 1;
            }
            else
            {
                num = num * 10 + *p - '0';
            }
            p++;
        }
    }
    if (num != 0)
        result += num;
    return result;
}