#include <stdio.h>
char * s_gets(char * st, int n)
{
    char * ret_val;

    ret_val = fgets(st, n, stdin);
    if (ret_val) //ret_val != NULL
    {
        while (*st != '\n' && *st != '\0')//加星号获取指针的值
            st++;
        if (*st == '\n')
            *st = '\0';//重新赋值，若不加星号则为初始化，应该是地址
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}