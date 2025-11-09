#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define LEN 40
char * s_gets(char * st, int n);
int atoi(char *ct);
int power(int pow, int n);
int main(void)
{
    char digits[LEN];
    printf("Please enter a string of digits: ");
    s_gets(digits, LEN);
    printf("%d", atoi(digits));
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
int atoi(char *ct)
{
    int result = 0;
    int length = strlen(ct);
    for (int num = 0; ct[num] != '\0'; num++)
        result += (ct[num] - '0') * power(10, length - 1 - num);
    return result;
}
int power(int pow, int n)
{
    int temp = 1;
    for (int num = 0; num < n; num++)
    {
        temp *= pow;
    }
    return temp;
}