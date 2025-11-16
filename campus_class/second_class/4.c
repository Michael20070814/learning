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
int main(void)
{
    char ar[] = "What you are?";
    print_chars(ar, strlen(ar));

    return 0;
}