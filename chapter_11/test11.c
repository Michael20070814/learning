#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LEN 40
char * s_gets(char * st, int n);
int get_strings(char (*str)[LEN]);
void print_origin(char (*str)[LEN], int n);
void print_ASCII(char (*str)[LEN], int n);
void print_length(char (*str)[LEN], int n);
void print_words_length(char (*str)[LEN], int n);
int first_words_length(char * ct);
int main(void)
{
    char decision;
    char ten_strings[10][40];
    char num;

    printf("Please enter ten strings: ");
    num = get_strings(ten_strings);
    printf("a:print orginals\t\tb:print strings in ASCII\n");
    printf("c:print in length\t\td:print in first word's length\n");
    printf("e:quit\n");
    printf("Please select one thing: ");
    while (scanf("%c", &decision) == 1 && decision != 'e')
    {
        while (getchar() != '\n')
            continue;
        switch(decision)
        {
            case 'a':
                print_origin(ten_strings, num);
                break;
            case 'b':
                print_ASCII(ten_strings, num);
                break;
            case 'c':
                print_length(ten_strings, num);
                break;
            case 'd':
                print_words_length(ten_strings, num);
                break;
            case 'e':
                break;
            default:
                printf("Please enter the correct alpha: ");
                break;
        }
        printf("a:print orginals\t\tb:print strings in ASCII\n");
        printf("c:print in length\t\td:print in first word's length\n");
        printf("e:quit\n");
        printf("Please select one thing: ");
        printf("Please select one thing:");
    }
    printf("Done!");
    
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
int get_strings(char (*str)[LEN])
{
    int num = 0;
    while (s_gets(str[num], LEN) != NULL && num < 9)
    {
        num++;
    }
    return num+1;
}
void print_origin(char (*str)[LEN], int n)
{
    for (int num = 0; num < n; num++)
        puts(str[num]);
}
void print_ASCII(char (*str)[LEN], int n)
{
    for (char temp = 'a'; temp <= 'z'; temp++)
    {
        for (int num = 0; num < n; num++)
        {
            if (*str[num] == temp)
                puts(str[num]);
        }
    }
}
void print_length(char (*str)[LEN], int n)
{
    char temp[LEN];
    for (int num = 0; num < n - 1; num++)
        for (int num1 = 0; num1 < n - 1; num1++)
            if (strlen(str[num1]) > strlen(str[num1 + 1]))
            {
                strcpy(temp, str[num1]);
                strcpy(str[num1], str[num1 + 1]);
                strcpy(str[num1 + 1], temp);
            }
    for (int num = 0; num < n; num++)
        puts(str[num]);
}
void print_words_length(char (*str)[LEN], int n)
{
    char temp[LEN];
    for (int num = 0; num < n - 1; num++)
        for (int num1 = 0; num1 < n - 1 - num; num1++)
            if (first_words_length(str[num1]) > first_words_length(str[num1 + 1]))
            {
                strcpy(temp, str[num1]);
                strcpy(str[num1], str[num1 + 1]);
                strcpy(str[num1 + 1], temp);
            }
    for (int num = 0; num < n; num++)
        puts(str[num]);
}
int first_words_length(char * ct)
{
    int num = 0;
    int num1;
    while (isspace(ct[num]))
        num++;
    num1 = num;
    while (!(isspace(ct[num])) && ct[num] != '\0')//访问数组元素警惕越界访问，我的输入结尾无空格，所以不结束
        num++;
    return num - num1;
}