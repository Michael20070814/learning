#include <stdio.h>
int main(void)
{
    char ch;
    int num = 0;
    while ((ch = getchar()) != '#')
    {
        if (ch == '.')
        {
            printf("!");
            num++;
        }
        else if (ch == '!')
        {
            num++;
            printf("!!");
        }
        else
            putchar(ch);
    }
    
    printf("I do %d replacement in total.", num);
    return 0;
}