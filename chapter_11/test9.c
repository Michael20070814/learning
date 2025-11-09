#include <stdio.h>
#include <string.h>
#define LEN 40
void swap(char * input)
{
    char temp;
    for (int num = 0; num < strlen(input) / 2; num++)//可以把字符串长度先保存下来，避免重复计算
    {
        temp = input[num];
        input[num] = input[strlen(input) - num - 1];
        input[strlen(input) - 1 - num] = temp;
    }
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
    char ch[40];

    printf("Please enter strings: ");
    while (s_gets(ch, LEN) != NULL)
    {
        puts(ch);
        swap(ch);
        printf("swaped: %s\n", ch);
        printf("Please enter another strings: (Enter EOF to quit)");
    }
    return 0;
}