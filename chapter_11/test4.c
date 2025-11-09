#include <stdio.h>
#include <string.h>
char * input(char *ct, int num);
int main(void)
{
    char ar[40];
    if (input(ar, 10))
        puts(ar);
    else
        puts("You are wrong!");
    return 0;
}
char * input(char *ct, int num)
{
    char ret_val;
    int n = 0;
    
    while ((ret_val = getchar()) != EOF &&(ret_val == ' ' || ret_val == '\t' || ret_val == '\n'))
        continue;
    if (ret_val == EOF || ret_val == '\n')
        return NULL;
    ct[n] = ret_val;
    n++;
    while ((ret_val = getchar()) != EOF && (ret_val != ' ' && ret_val != '\t' && ret_val != '\n') && n < num)
    {
        ct[n] = ret_val;
        n++;
    }
    ct[n] = '\0';
    if (ret_val != '\n' && ret_val != EOF)
        while (getchar() != '\n')//丢弃输入行剩下的内容
            continue;
    return ct;
}