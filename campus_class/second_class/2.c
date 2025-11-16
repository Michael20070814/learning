#include <stdio.h>

int main(void)
{
    char s[] = "13579";
    printf("s at %X\n", &s);
    for (int i = 0; i < 6; i++)
    {
        printf("value :%c (%x); index: %d; and address: %X\n", s[i], s[i], i, &(s[i]));
    }
    return 0;
}