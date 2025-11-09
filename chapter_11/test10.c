#include <stdio.h>
#include <string.h>
#define LEN 40
char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;

    ret_val = fgets(st, n, stdin);
    if (ret_val) //ret_val != NULL
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
char *delete_space(char * input)//也可以直接使用原数组覆写
{
    char temp[LEN];
    int n = 0;
    int num1 = 0;
    for (int num = 0; input[num] != '\0'; num++)
    {
        if (input[num] != ' ')
        {
            temp[n] = input[num];
            n++;
        }
    }
    for (num1 = 0; num1 < n; num1++)
        input[num1] = temp[num1];
    input[num1] = '\0';

    return input;
}
int main(void)
{
    char ch[LEN];
    printf("Please enter strings: ");
    while (s_gets(ch, LEN) != NULL)
    {
        puts(ch);
        delete_space(ch);
        puts(ch);
        printf("Please enter another strings: ");
    }

    return 0;
}