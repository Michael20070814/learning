#include <stdio.h>
#include <ctype.h>
char get_first(void);
int main(void)
{
    int letter;
    letter = get_first();
    putchar(letter);
    return 0;
}
char get_first(void)
{
    int ch;
    do
    {

    }
    while (isspace(ch = getchar()));
    while (getchar() != '\n')
        continue;
    return ch;
}