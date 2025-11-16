#include <stdio.h>

int main(void)
{
    char s[] = "13579", *p;
    p = s;
    p = p + 2;
    char a = *(p + 1);
    a = *(p + 2);
    return 0;
}