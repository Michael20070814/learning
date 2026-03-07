#include <stdio.h>
#include <ctype.h>

int main()
{
    int index = 0;
    char s[1000];

    scanf("%s", s);
    while(s[index] != '\0')
    {
        if (s[index] == '-')
        {
            if ((islower(s[index - 1]) && islower(s[index + 1])) || (isupper(s[index - 1]) && isupper(s[index + 1])) || 
            (isdigit(s[index - 1]) && isdigit(s[index + 1])))
            {
                char *p = &s[index - 1];
                while (*p != s[index + 1] - 1)
                {    
                    *p = *p + 1;
                    putc(*p, stdout);
                }
            }
            else
                putc('-', stdout);
        }
        else
            fputc(s[index], stdout);
        index++;
    }
}