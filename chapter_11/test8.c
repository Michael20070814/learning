#include <stdio.h>
#include <stdbool.h>
#define LEN 40
char * string_in(char * st, char *ct)
{
    bool value = 1;
    for (int count = 0; st[count] != '\0'; count++)
    {
        if (st[count] == *ct)
        {
            for (int num = 0; ct[num] != '\0'; num++)
            {
                if (st[count + num] == ct[num] && st[count + num] != '\0')
                    value *= 1;
                else//else只作用于紧跟的语句
                {
                    value = 0;
                    break;
                }
            }
            if (value)
                return st + count;
        }
        value = 1;
    }
    return NULL;
}
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
int main(void)
{
    char input[LEN];
    char search[LEN];
    printf("Please enter strings:");
    while (s_gets(input, LEN) != NULL)
    {
        printf("Please enter the strings you want to search for: ");
        if (s_gets(search, LEN) != NULL)
        {
            if (string_in(input, search))
                puts(string_in(input, search));//如果返回值是null，puts会崩溃
            else
                printf("%s is not in the string\n", search);
            printf("Please enter another strings(Enter EOF to quit)");
        }
    }
    return 0;
}