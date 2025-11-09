#include <stdio.h>
int strlen1(char *st)
{
    int result = 0;

    while (*st != '\0')
    {
        st++;
        result += 1;
    }
    return result;
}
int main(void)
{
    char clause[] = "Hello world";

    printf("%d", strlen1(clause));
    return 0;
}