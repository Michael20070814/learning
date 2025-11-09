#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define LEN 40
char * s_gets(char * st, int n);
int find_upper(char *st, int n);
int find_lower(char *st, int n);
int find_punct(char *st, int n);
int find_digit(char *st, int n);
int main(void)
{
    char strings[LEN];

    printf("Please enter a strings: ");
    while (s_gets(strings, LEN) != NULL)
        continue;
    printf("total words: %d\n", strlen(strings));
    printf("upper number: %d\n", find_upper(strings, strlen(strings)));
    printf("lower number: %d\n", find_lower(strings, strlen(strings)));
    printf("punct number: %d\n", find_punct(strings, strlen(strings)));
    printf("digit number: %d\n", find_digit(strings, strlen(strings)));

    return 0;
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
int find_upper(char *st, int n)
{
    int upper_num = 0;
    for (int num = 0; num < n; num++)
    {
        if (isupper(st[num]))
            upper_num += 1;
    }
    return upper_num;
}
int find_lower(char *st, int n)
{
    int lower_num = 0;
    for (int num = 0; num < n; num++)
    {
        if (islower(st[num]))
            lower_num += 1;
    }
    return lower_num;
}
int find_punct(char *st, int n)
{
    int punct_num = 0;
    for (int num = 0; num < n; num++)
    {
        if (ispunct(st[num]))
            punct_num += 1;
    }
    return punct_num;
}
int find_digit(char *st, int n)
{
    int digit_num = 0;
    for (int num = 0; num < n; num++)
    {
        if (isdigit(st[num]))
            digit_num += 1;
    }
    return digit_num;
}