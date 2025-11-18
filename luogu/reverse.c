#include <stdio.h>
void reverse_int(char * s, int size);//整数反转
void reverse_float(char * s, int size);/*小数反转*/
void reverse_fraction(char *s, int size);/*分数反转*/
void reverse_percentage(char *s, int size);/*百分数反转*/
int main(void)
{
    char input[50];
    int value, num;
    value = 1;
    
    scanf("%s", input);
    for (num = 0; input[num] != '\0'; num++)
    {
        if (input[num] == '.')
            value *= 2;
        else if (input[num] == '/')
            value *= 3;
        else if (input[num] == '%')
            value *= 4;
        else
            value *= 1;
    }
    switch (value)
    {
        case 1:
        reverse_int(input, num);
        printf("\n");
        break;
        case 2:
        reverse_float(input, num);
        printf("\n");
        break;
        case 3:
        reverse_fraction(input, num);
        printf("\n");
        break;
        case 4:
        reverse_percentage(input, num);
        printf("\n");
        break;
    }
    
    return 0;
}
void reverse_int(char * s, int size)
{
    int n;
    for (n = size - 1; s[n] == '0' && n >= 0; n--)
        continue;
    if (n == -1)
        printf("0");
    else
        for (; n >= 0; n--)
            printf("%c", s[n]);
}
void reverse_float(char * s, int size)
{
    int n, temp, order;

    for (n = 0; s[n] != '.'; n++)
        continue;
    temp = n;
    reverse_int(s, temp);
    printf(".");
    for (n = size - 1; s[n] == '0' && s[n] != '.'; n--)
        continue;
    for (order = temp + 1; s[order] == '0'; order++)
        continue;
    if (n == temp)
        printf("0");
    else
        for (n = size - 1 ; n >= order; n--)
            printf("%c", s[n]);
}
void reverse_fraction(char *s, int size)
{
    int n, temp, order;

    for (n = 0; s[n] != '/'; n++)
        continue;
    temp = n;
    reverse_int(s, temp);
    printf("/");
    for (n = size - 1; s[n] == '0' && s[n] != '/'; n--)
        continue;
    for (order = temp + 1; s[order] == '0'; order++)
        continue;
    if (n == temp)
        printf("0");
    else
    {   
        for (n = size - 1; n >= order && s[n] == '0'; n--)
            continue;
        for (; n >= order; n--)
            printf("%c", s[n]);
    }
}
void reverse_percentage(char *s, int size)
{
    reverse_int(s, size - 1);
    printf("%%");
}