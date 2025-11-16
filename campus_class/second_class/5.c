#include <stdio.h>
#include <string.h>
void print_chars(char s[], int size)
{
    char *p, *q;
    p = s;
    q = s + size - 1;
    for (; p <= q; p++)
    {
        printf("%c", *p);
    }  
}
char *find_char(char *p, char *q, char word)
{
    for ( ; p <= q; p++)
    {
        if (*p == word)
            return p;
    }
    return NULL;
}
int main(void)
{
    int size;
    char ch[50];
    gets(ch);
    size = strlen(ch);
    print_chars(find_char(&ch[0], &ch[size - 1], 'f'), size);

    return 0;
}