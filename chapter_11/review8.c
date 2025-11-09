#include <stdio.h>
int main(void)
{
    char str1 [ ] = "gawsie";
    char *ps;
    int i = 0;
    for (ps = str1; *ps != '\0'; ps++)
    {
        if (*ps == 'a' || *ps == 'e')
            putchar(*ps);
        else
            (*ps)--;//没有putchar，只在后面输出一次
        putchar(*ps);
    }
    return 0;
}