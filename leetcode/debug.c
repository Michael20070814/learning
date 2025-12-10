#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* reverseWords(char* s) 
{
    char *p = s;
    char *q = s;
    int length, i = 0;
    while (*p == ' ')
    {
        p++;
        continue;
    }
    while (*p != '\0')
    {
        if (*p != ' ' || (*(p + 1) != ' ' && *(p + 1) != '\0'))
        {
            *q = *p;
            p++;
            q++;
        }
        else
            p++;
    }
    *q = '\0';
    length = strlen(s);
    char *result = malloc(length * (sizeof(char) + 1));
    for (int num = length - 1; num >= 0; num--)
    {
        if (s[num] == ' ')
        {
            int n = num + 1;
            while (s[n] != ' ' && s[n] != '\0')
            {
                result[i] = s[n];
                i++;
                n++;
            }
            result[i++] = ' ';
        }
        else if (num == 0)
        {
            int n = num;
            while (s[n] != ' ' && s[n] != '\0')
            {
                result[i] = s[n];
                i++;
                n++;
            }
            result[i++] = ' ';
        }
    }
    result[i - 1] = '\0';

    return result;
}
int main(void)
{
    char input[] = "  hello world  ";
    reverseWords(input);

    return 0;
}