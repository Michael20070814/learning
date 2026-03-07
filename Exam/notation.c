#include <stdio.h>
#include <string.h>
void input(char s[]);
int load(char s[]);
int main()
{
    char s[1000];
    input(s);

    int num = load(s);

    printf(s);
    putc('e', stdout);
    printf("%d", num);
}
void input(char s[])
{
    scanf("%s", s);
}
int load(char s[])
{
    char *p = s;
    int small_index = 1;
    int big_index = 0;
    int index = 0;
    if (*p == '0')
    {
        p = p + 2;
        while (*p == '0')
        {
            p++;
            small_index++;
        }
        s[index++] = *p;
        p++;
        if (*p != '\0')
            s[index++] = '.';
        while (*p != '\0')
        {
            s[index++] = *p;
            p++;
        }
        s[index] = '\0';
        return (-small_index);
    }
    else
    {
        p++;
        while (*p != '.')
        {
            p++;
            big_index++;
        }
        p = s;
        if (big_index != 0)
        {
            int m = 0;
            char temp[strlen(s) + 1];
            strcpy(temp, s);
            s[index++] = temp[m++];
            s[index++] = '.';
            while (temp[m] != '\0')
            {
                if (temp[m] != '.')
                    s[index++] = temp[m];
                m++;
            }
        }
        return big_index;
    }
    
}