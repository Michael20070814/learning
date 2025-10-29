#include <stdio.h>
#include <ctype.h>
int alpha(char ch);
int main(void)
{
    char ch;
    while ((ch = getchar()) != EOF)
    {
        printf("%d ", alpha(ch));
    }
    return 0;
}
int alpha(char ch)
{
    if (islower(ch))
    {
        return (ch - 96);
    }
    else if (isupper(ch))
    {
        return (ch - 64);
    }
    else
        return -1;
}