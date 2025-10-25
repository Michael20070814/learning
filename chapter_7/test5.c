#include <stdio.h>
int main(void)
{
    char ch;
    int num = 0;
    while ((ch = getchar()) != '#')
    {
        switch (ch)
        {
        case '.':
            printf("!");
            num++;
            break;
        case '!':
            num++;
            printf("!!");
            break;
        default:
            putchar(ch);
            break;
        }
    }
    
    printf("I do %d replacement in total.", num);
    return 0;
}